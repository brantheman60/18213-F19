/*
 * 15-213/18-213: Introduction to Computer Systems
 * Name: Brandon Wang
 * AndrewID: bcwang
 *
 * Sources:
 * -Lecture 19: Exceptional Control Flow: Exceptions and Processes
 *  used example code from slides as starter code
 */

/*
 * TODO: Delete this comment and replace it with your own.
 * tsh - A tiny shell program with job control
 * <The line above is not a sufficient documentation.
 *  You will need to write your program documentation.
 *  Follow the 15-213/18-213/15-513 style guide at
 *  http://www.cs.cmu.edu/~213/codeStyle.html.>
 */

#include "csapp.h"
#include "tsh_helper.h"

#include <sys/wait.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * If DEBUG is defined, enable contracts and printing on dbg_printf.
 */
#ifdef DEBUG
/* When debugging is enabled, these form aliases to useful functions */
#define dbg_printf(...) printf(__VA_ARGS__)
#define dbg_requires(...) assert(__VA_ARGS__)
#define dbg_assert(...) assert(__VA_ARGS__)
#define dbg_ensures(...) assert(__VA_ARGS__)
#else
/* When debugging is disabled, no code gets generated for these */
#define dbg_printf(...)
#define dbg_requires(...)
#define dbg_assert(...)
#define dbg_ensures(...)
#endif

/* Function prototypes */
void eval(const char *cmdline);
void do_bgfg(char *argv[]);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);
void sigquit_handler(int sig);
void cleanup(void);

/*
 * main: shell's main routine that accepts initial ./tsh flags, installs
 *       the signal handlers, and continuously evaluates every command
 *       line inputted in the shell. Less importantly, it creates the
 *       environmental variable MY_ENV and exits if a function call fails.
 * Input: int argc (number of command line arguments)
 *        char **argv (list of command line arguments)
 * Output: int (doesn't really matter...)
 */
int main(int argc, char **argv) {
  char c;
  char cmdline[MAXLINE_TSH]; // Cmdline for fgets
  bool emit_prompt = true;   // Emit prompt (default)

  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  if (dup2(STDOUT_FILENO, STDERR_FILENO) < 0) {
    perror("dup2 error");
    exit(1);
  }

  // Parse the command line
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h': // Prints help message
      usage();
      break;
    case 'v': // Emits additional diagnostic info
      verbose = true;
      break;
    case 'p': // Disables prompt printing
      emit_prompt = false;
      break;
    default:
      usage();
    }
  }

  // Create environment variable
  if (putenv("MY_ENV=42") < 0) {
    perror("putenv");
    exit(1);
  }

  // Set buffering mode of stdout to line buffering.
  // This prevents lines from being printed in the wrong order.
  if (setvbuf(stdout, NULL, _IOLBF, 0) < 0) {
    perror("setvbuf");
    exit(1);
  }

  // Initialize the job list
  init_job_list();

  // Register a function to clean up the job list on program termination.
  // The function may not run in the case of abnormal termination (e.g. when
  // using exit or terminating due to a signal handler), so in those cases,
  // we trust that the OS will clean up any remaining resources.
  if (atexit(cleanup) < 0) {
    perror("atexit");
    exit(1);
  }

  // Install the signal handlers
  Signal(SIGINT, sigint_handler);   // Handles Ctrl-C
  Signal(SIGTSTP, sigtstp_handler); // Handles Ctrl-Z
  Signal(SIGCHLD, sigchld_handler); // Handles terminated or stopped child

  Signal(SIGTTIN, SIG_IGN);
  Signal(SIGTTOU, SIG_IGN);

  Signal(SIGQUIT, sigquit_handler);

  // Execute the shell's read/eval loop
  while (true) {
    if (emit_prompt) {
      printf("%s", prompt);

      // We must flush stdout since we are not printing a full line.
      fflush(stdout);
    }

    if ((fgets(cmdline, MAXLINE_TSH, stdin) == NULL) && ferror(stdin)) {
      perror("fgets error");
      exit(1);
    }

    if (feof(stdin)) {
      // End of file (Ctrl-D)
      printf("\n");
      return 0;
    }

    // Remove any trailing newline
    char *newline = strchr(cmdline, '\n');
    if (newline != NULL) {
      *newline = '\0';
    }

    // Evaluate the command line
    eval(cmdline);
  }

  return -1; // control never reaches here
}

/** unix_error: safetly prints error message and exits **/
void unix_error(char *msg) {
  sio_printf("%s: %s\n", msg, strerror(errno));
  _exit(-1);
}

/*
 * eval: long-running process that reads a single command line and runs
 *       its builtin/foreground/background tasks. It properly creates and
 *       manipulates parent and child processes, and it blocks certain
 *       signals when necessary.
 * Input: const char *cmdline (pointer to the entire command line)
 * Output: void
 */
void eval(const char *cmdline) {
  parseline_return parse_result;
  struct cmdline_tokens token;

  // Parse command line
  parse_result = parseline(cmdline, &token);

  if (parse_result == PARSELINE_ERROR || parse_result == PARSELINE_EMPTY) {
    return;
  }

  // TODO: Code here!
  pid_t pid;

  sigset_t mask, mask_all, prev_mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGTSTP);
  sigfillset(&mask_all);

  switch (token.builtin) {
  case BUILTIN_QUIT:
    _exit(0);
    break;
  case BUILTIN_JOBS:
    // Block all 3 signals
    sigprocmask(SIG_BLOCK, &mask, &prev_mask);
    list_jobs(STDOUT_FILENO);
    sigprocmask(SIG_SETMASK, &prev_mask, NULL); // restore signal

    return;
    break;
  case BUILTIN_BG:
    do_bgfg(token.argv);
    return;
    break;
  case BUILTIN_FG:
    do_bgfg(token.argv);
    return;
    break;
  case BUILTIN_NONE:
    // Block all 3 signals until reaches child/parent process
    sigprocmask(SIG_BLOCK, &mask, &prev_mask);

    // Fork
    if ((pid = fork()) < 0)
      unix_error("Error in fork");

    // Child process
    if (pid == 0) {
      //sigprocmask(SIG_SETMASK, &prev_mask, NULL); // restore signal
      sigprocmask(SIG_UNBLOCK, &mask, NULL); // restore signal
      if (setpgid(0, 0) < 0)
      {
        unix_error("Error in setpgid\n");
      }

      if (execve(token.argv[0], token.argv, environ) < 0) {
        sio_printf("%s: Command not found\n", token.argv[0]);
        _exit(-1);
      }
    }

    // Parent process
    sigprocmask(SIG_BLOCK, &mask_all, NULL);
    if (parse_result == PARSELINE_FG) // foreground task
    {
      add_job(pid, FG, cmdline);
      sigprocmask(SIG_SETMASK, &prev_mask, NULL); // restore signal
      waitfg(pid);
    } else if (parse_result == PARSELINE_BG) // background task
    {
      add_job(pid, BG, cmdline);
      jid_t jid = job_from_pid(pid);
      const char* buf = job_get_cmdline(jid);
      sigprocmask(SIG_SETMASK, &prev_mask, NULL); // restore signal
      sio_printf("[%d] (%d) %s\n", jid, pid, buf);
    } else
    {
      unix_error("Job is neither foreground nor background!\n");
    }
    break;
  default:
    sio_printf("Should not reach this code\n");
  }
  return;
}

/*
 * do_bgfg: perform builtin bg and fg commands by taking in a PID or JID
 *          from the argument list then setting the job to a foreground or
 *          a background task
 * Input: char *argv[] (argument list represented by array of strings;
 *                     the second argument should be the PID/JID)
 * Output: void
 */

void do_bgfg(char *argv[]) {
  if(argv[1] == NULL || argv[2] != NULL) //exactly 2 proper arguments
  {
    sio_printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }

  jid_t jid;
  pid_t pid;
  sigset_t mask, prev_mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGTSTP);
  sigprocmask(SIG_BLOCK, &mask, &prev_mask);

  char first_char = argv[1][0]; // first character of 2nd argument
  if (first_char != '%') // argument is PID
  {
    if(!isdigit(argv[1][0]))
    {
      sio_printf("%s: argument must be a PID or %%jobid\n",
            argv[0]);
      return;
    }
    pid = atoi(argv[1]);
    if (pid == 0) {
      sio_printf("%s: argument must be a PID or %%jobid\n",
            argv[0]);
      return;
    }
    jid = job_from_pid(pid);
    if (jid == 0) {
      sio_printf("(%d): No such process\n", pid);
      return;
    }
  }

  else // argument is JID
  {
    if(!isdigit(argv[1][1]))
    {
      sio_printf("%s: argument must be a PID or %%jobid\n",
            argv[0]);
      return;
    }
    jid = atoi(argv[1] + 1);
    if (jid == 0 || !job_exists(jid)) { //invalid job
      sio_printf("%s: No such job\n", argv[1]);
      return;
    }
    pid = job_get_pid(jid);
  }

  // kill process group and process job command
  kill(-pid, SIGCONT);
  if (!strcmp(argv[0], "bg")) // bg command
  {
    job_set_state(jid, BG);
    sio_printf("[%d] (%d) %s\n", jid, pid, job_get_cmdline(jid));
  } else {
    job_set_state(jid, FG); // fg command
    waitfg(pid);
  }
  sigprocmask(SIG_SETMASK, &prev_mask, NULL); // restore signal

  return;
}

/*
 * waitfg: block/wait until process is no longer foreground process
 * Input: pid_t pid (Process ID to be waiting on)
 * Output: void
 */
void waitfg(pid_t pid) {
  sigset_t mask, prev;
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGTSTP);
  sigfillset(&mask); /////
  sigprocmask(SIG_BLOCK, &mask, &prev);
  sigemptyset(&prev); /////

  //block until no longer foreground process
  while (fg_job() != 0 && pid == job_get_pid(fg_job()))
    sigsuspend(&prev);

  if(verbose)
    sio_printf("waitfg: Process (%d) no longer the fg process\n", pid);

  sigprocmask(SIG_SETMASK, &prev, NULL);
  return;
}

/*****************
 * Signal handlers
 *****************/

/*
 * sigchld_handler: receives a SIGCHLD signal when a child is terminated/
 *                  stopped, then reaps the children of the parent process.
 * Input: int sig (the number associated with the SIGCHLD signal)
 * Output: void
 */
void sigchld_handler(int sig) {
  int olderrno = errno;
  sigset_t mask, prev_mask;
  pid_t pid;
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGTSTP);

  if (verbose)
    sio_printf("sigchld_handler: entering\n");

  int status;
  while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
    sigprocmask(SIG_BLOCK, &mask, &prev_mask); // block all 3 signals
    jid_t jid = job_from_pid(pid);
    if (jid == 0)  // no job
    {
      sio_printf("No such child available.\n");
      return;
    }

    if(WIFSTOPPED(status)) //process is stopped
    {
      job_set_state(jid, ST);
      sio_printf("Job [%d] (%d) stopped by signal %d\n",
            jid, pid, WSTOPSIG(status));
    }
    else if(WIFSIGNALED(status)) //process is signalled
    {
      delete_job(jid);
      sio_printf("Job [%d] (%d) terminated by signal %d\n",
            jid, pid, WTERMSIG(status));
    }
    else if(WIFEXITED(status)) //process is exited
    {
      delete_job(jid);
      if (verbose) {
        sio_printf("sigchld_handler: Job [%d] (%d) deleted\n", jid, pid);
        sio_printf("sigchld_handler: Job [%d] (%d)", jid, pid);
        sio_printf(" terminated normally (status %d)\n", status);
      }
    }
    else
    {
      unix_error("Error in waitpid\n");
    }

    sigprocmask(SIG_SETMASK, &prev_mask, NULL); // block all signals
  }
  //if (errno != ECHILD)
  //  unix_error("waitpid error\n"); ///////////

  if (verbose)
    sio_printf("sigchld_handler: exiting\n");
  errno = olderrno;
  return;
}

/*
 * sigint_handler: sends a SIGINT signal to the shell when Ctrl-c is typed,
 *                 thus ending the foreground processes
 * Input: int sig (the number associated with the SIGINT signal)
 * Output: void
 */
void sigint_handler(int sig) {
  int olderrno = errno;
  sigset_t mask, prev_mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);
  sigaddset(&mask, SIGTSTP);
  sigprocmask(SIG_BLOCK, &mask, &prev_mask);

  if (verbose)
    sio_printf("sigint_handler: entering\n");

  jid_t jid = fg_job();
  if(jid == 0) // no foreground job
  {
    errno = olderrno;
    return;
  }

  pid_t pid = job_get_pid(jid);
  if (pid != 0) {
    if (verbose)
      sio_printf("sigint_handler: Sent SIGINT to Job [%d] (%d)\n",
                jid, pid);
    kill(-pid, SIGINT); // send to all process group IDs
  }
  sigprocmask(SIG_SETMASK, &prev_mask, NULL); // restore signal

  if (verbose)
    sio_printf("sigint_handler: exiting\n");
  errno = olderrno;
  return;
}

/*
 * sigtstp_handler: sends a SIGSTP signal to the shell when Ctrl-c is typed,
 *                  thus suspending the foreground processes
 * Input: int sig (the number associated with the SIGTSTP signal)
 * Output: void
 */
void sigtstp_handler(int sig) {
  int olderrno = errno;
  sigset_t mask, prev_mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGCHLD);
  sigaddset(&mask, SIGINT);
  sigprocmask(SIG_BLOCK, &mask, &prev_mask);

  if (verbose)
    sio_printf("sigtstp_handler: entering\n");

  jid_t jid = fg_job();
  if(jid == 0) // no foreground job
  {
    errno = olderrno;
    return;
  }

  pid_t pid = job_get_pid(jid);
  if (pid != 0) {
    if (verbose)
    {
      sio_printf("sigint_handler: Sent SIGTSTP to Job [%d] (%d)\n",
             jid, pid);
    }
    kill(-pid, SIGTSTP); // send to all process group IDs
  }
  else
    unix_error("Error in job_get_pid\n");
  sigprocmask(SIG_SETMASK, &prev_mask, NULL); // restore signal

  if (verbose)
    sio_printf("sigtstp_handler: exiting\n");
  errno = olderrno;
  return;
}

/*
 * cleanup - Attempt to clean up global resources when the program exits. In
 * particular, the job list must be freed at this time, since it may contain
 * leftover buffers from existing or even deleted jobs.
 */
void cleanup(void) {
  // Signals handlers need to be removed before destroying the joblist
  Signal(SIGINT, SIG_DFL);  // Handles Ctrl-C
  Signal(SIGTSTP, SIG_DFL); // Handles Ctrl-Z
  Signal(SIGCHLD, SIG_DFL); // Handles terminated or stopped child

  destroy_job_list();
}

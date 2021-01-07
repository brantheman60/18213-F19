serve s1
generate random-text03.txt 2K
request r03a random-text03.txt s1
request r03b random-text03.txt s1
request r03c random-text03.txt s1
wait *
# These responses are all of the same file.  Only one should be cached
# Out of order response will cause sequential proxy to fail
respond r03a r03b r03c
wait *
check r03a
check r03b
check r03c
quit

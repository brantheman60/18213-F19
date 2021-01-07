# Make sure cache holds at most one copy of a binary file
serve s1
generate random-binary00.bin 100K
generate random-binary01.bin 100K
generate random-binary02.bin 100K
generate random-binary03.bin 100K
generate random-binary04.bin 100K
generate random-binary05.bin 100K
generate random-binary06.bin 100K
generate random-binary07.bin 100K
generate random-binary08.bin 100K
generate random-binary09.bin 100K
# Make 5 requests, but defer responses
request r05a random-binary05.bin s1
request r06a random-binary06.bin s1
request r07a random-binary07.bin s1
request r08a random-binary08.bin s1
request r09a random-binary09.bin s1
wait *
# Use 500K of cache, filling it up
fetch f05 random-binary05.bin s1
fetch f06 random-binary06.bin s1
fetch f07 random-binary07.bin s1
fetch f08 random-binary08.bin s1
fetch f09 random-binary09.bin s1
wait *
# Out of order response will cause sequential proxy to fail
respond r08a r09a r05a r06a r07a
wait *
check f05
check f06
check f07
check f08
check f09
check r05a
check r06a
check r07a
check r08a
check r09a
quit

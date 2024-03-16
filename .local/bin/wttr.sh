#!/bin/bash

# This function checks if wttr.in is available before the weather info is fetched
ck_curl() {
	curl -sf pt.wttr.in > /dev/null
}

ck_curl
if [ $? -eq 0 ]					# $? means "output of the last command"
then
	curl -s pt.wttr.in/?format="%C,+%t\n" > /tmp/wttr
	wttr_net=1
else						# Non-zero output would appear both when the site \
	for (( cntr = 0; cntr < 3; cntr++ ))	#   is down and when you're physically offline
	do
		echo "Probing.  " > /tmp/wttr
		sleep 0.5
		echo "Probing.. " > /tmp/wttr
		sleep 0.5
		echo "Probing..." > /tmp/wttr
		sleep 0.5			# A wee bit of animation
	done
	ck_curl					# Online check is rerun only once, if the first check fails.
fi						#   In case you're using wifi, and the cron job runs before \
						#   it authenticates
if ! [ $wttr_net ]
then echo "Offline fr :'( " > /tmp/wttr
fi

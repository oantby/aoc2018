import operator
import sys
import datetime

sleep_times = {}
with open('4in.txt', 'r') as file:
	for line in file.readlines():
		stamp = datetime.datetime.strptime(line[:18], '[%Y-%m-%d %H:%M]')
		line = line.strip()
		if line[-12:] == 'begins shift':
			# new guard taking over.
			cur_guard = int(line[26:-13])
		elif line[-12:] == 'falls asleep':
			start = stamp
		elif line[-8:] == 'wakes up':
			if not cur_guard in sleep_times:
				sleep_times[cur_guard] = []
			sleep_times[cur_guard].append((start, stamp))
			start = None

max_guard = None
max_sum = 0
minutes = {}
guard_max = {}
for guard in sleep_times:
	for x in sleep_times[guard]:
		if not guard in minutes: minutes[guard] = {}
		for i in range(x[0].minute, x[1].minute):
			if not i in minutes[guard]: minutes[guard][i] = 0
			minutes[guard][i] += 1
	guard_max[guard] = max(minutes[guard].iteritems(), key=operator.itemgetter(1))



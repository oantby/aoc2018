import pprint
import sys
import operator

data = [
(342, 203),
(79, 64),
(268, 323),
(239, 131),
(246, 87),
(161, 93),
(306, 146),
(43, 146),
(57, 112),
(241, 277),
(304, 303),
(143, 235),
(253, 318),
(97, 103),
(200, 250),
(67, 207),
(345, 149),
(133, 222),
(232, 123),
(156, 359),
(80, 224),
(51, 145),
(138, 312),
(339, 294),
(297, 256),
(163, 311),
(241, 321),
(126, 66),
(145, 171),
(359, 184),
(241, 58),
(108, 312),
(117, 118),
(101, 180),
(58, 290),
(324, 42),
(141, 190),
(270, 149),
(209, 294),
(296, 345),
(68, 266),
(233, 281),
(305, 183),
(245, 230),
(161, 295),
(335, 352),
(93, 66),
(227, 59),
(264, 249),
(116, 173)
]

# data = [
# (1, 1),
# (1, 6),
# (8, 3),
# (3, 4),
# (5, 5),
# (8, 9)
# ]

dimx = 359
dimy = 359

closest = {}
r = []
for i in range(dimx):
	for j in range(dimy):
		total_dist = 0
		for coord in data:
			
			dist = abs(i-coord[0]) + abs(j-coord[1])
			total_dist += dist
		print("Point (%d, %d) total distance: %d" % (i, j, total_dist))
		if total_dist < 10000:
			r.append((i,j))
pprint.PrettyPrinter(indent=4).pprint(r)

print(len(r))

# counter = {}
# for i in closest:
# 	if closest[i] is None: continue
# 	if not closest[i] in counter: counter[closest[i]] = 0
# 	if counter[closest[i]] is None: continue
# 	if (i+1)%dimy in [0,1] or (i+1)/dimx in [0,1]: counter[closest[i]] = None; continue
# 	counter[closest[i]] += 1
# 
# t = max(counter.iteritems(), key=operator.itemgetter(1))
# print counter
# print(t)

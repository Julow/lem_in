#!/usr/bin/python
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    longlong.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/08 15:38:34 by jaguillo          #+#    #+#              #
#    Updated: 2015/06/08 15:40:22 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from sys import argv

# Usage: ./longlong.py [length] [ants]

count = 50000
ants = 50

if len(argv) > 1:
	count = int(argv[1])
	if len(argv) > 2:
		ants = int(argv[2])

print("%d" % ants)
print("##start")
print("start 0 1")
print("##end")
print("end 3 0")

for i in range(0, count):
	print("%d %d %d" % (i, i, i))

print("start-0")

for i in range(1, count):
	print("%d-%d" % (i - 1, i))

print("end-%d" % (count - 1))

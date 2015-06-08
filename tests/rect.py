#!/usr/bin/python
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rect.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/08 15:30:52 by jaguillo          #+#    #+#              #
#    Updated: 2015/06/08 15:48:03 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from sys import argv

# Usage: ./rect.py [width [height]] [ants]

# default values
width = 8
height = 6
ants = 20

if len(argv) > 1:
	width = int(argv[1])
	if len(argv) > 2:
		height = int(argv[2])
		if len(argv) > 3:
			ants = int(argv[3])

print("%d" % ants)

for i in range(0, width):
	for j in range(0, height):
		if i == 0 and j == 0:
			print("##start")
		elif i == width - 1 and j == height - 1:
			print("##end")
		print("%d/%d %d %d" % (i, j, i, j))

for i in range(0, width):
	for j in range(0, height):
		if i > 0:
			print("%d/%d-%d/%d" % (i - 1, j, i, j))
		if j > 0:
			print("%d/%d-%d/%d" % (i, j - 1, i, j))

#!/usr/bin/python
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    gen.py                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juloo <juloo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/06/06 17:26:28 by juloo             #+#    #+#              #
#    Updated: 2015/06/08 14:51:17 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from sys import argv, exit
from random import randint

if len(argv) <= 1:
	print("Not enougth argument")
	print("Usage: %s rooms [ants]")
	exit()

rooms = int(argv[1])

ants = int(argv[2]) if len(argv) > 2 else 5

print("%d" % ants)
print("#")
print("# Rooms: %d" % rooms)
print("# Ants: %d" % ants)
print("#")
print("##start")
print("0 0 0")
print("##end")
print("1 0 0")

for i in range(2, rooms):
	print("%d 0 0" % i)

for i in range(0, rooms):
	for j in range(2, rooms):
		if randint(0, 2) == 0:
			print("%d-%d" % (i, j))

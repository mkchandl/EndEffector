# -*- coding: utf-8 -*-
"""
Created on Tue Nov 30 18:40:46 2021

@author: Cole
"""

import math

theta1 = 0;
theta2 = 30;
theta3 = 15;
l1 = 2;
l2 = 1.67;
l3 = 1;

x = math.sin(math.radians(theta1))*(l1 + l2*math.cos(math.radians(theta2)) + l3*math.cos(math.radians(theta2 + theta3)));
y = l2*math.sin(math.radians(theta2)) + l3*math.sin(math.radians(theta2 + theta3));
z = math.cos(math.radians(theta1))*(l1 + l2*math.cos(math.radians(theta2)) + l3*math.cos(math.radians(theta2 + theta3)));

print(x);
print(y);
print(z);
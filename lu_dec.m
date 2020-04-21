clc
clear all

A = [3   2   1   3;
   4   1   1   2;
   2   1   4   3;
   3   2   1   4];
   
U = A;
m = size(A, 1);
L =eye(m);
L
U
printf("[%dx%d]\n",0, 0);
keyboard
for col = 1:m-1
  for row=col+1:m
    L(row,col) = U(row,col)/U(col, col);
    U(row, col:m) = U(row, col:m) - L(row,col) * U(col, col:m);
    L
    U
    printf("[%dx%d]\n", row - 1, col - 1);
    keyboard
  endfor
endfor

clear all;
clc;

A = [12, -1, -1, 0; -1, 12, -1, -1; -1, -1 12, -1; 0, -1, -1, 12];

U = A;
L = eye(4);

m = size(A,1);

for i=1:m
   b(i,1) = sin((i-1)*6);
end

for k=1:m-1
   for j = k+1:m
      L(j,k) = U(j,k)/U(k,k);
      U(j,k:m) = U(j,k:m) - L(j,k) * U(k,k:m);
   end
end

Y = L\b;
X = U\Y;

X



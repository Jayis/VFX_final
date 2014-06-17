function [mask] = points2mask( Quad,img )
%make a quad_mask on img
%   points needs to arranged in counter-clockwise
tic
% constant
n = length(Quad);
h = size(img,1);
w = size(img,2);
% pre-allocattion
mask = zeros(h,w);
vec1 = [0; 0; 0];
vec2 = [0; 0; 0];
% find min&max of x[]&y[]
x = [];
y = [];
for t = 1:n
    x = [x Quad{t}(2)];
    y = [y Quad{t}(1)]; 
end
x_sort = sort(x);
y_sort = sort(y);
% find points inside Quad, and add to queries
queries = [];
for i = floor(y_sort(1)):ceil(y_sort(n))
   for j = floor(x_sort(1)):ceil(x_sort(n))
       cur_point = [i; j];
       satis = 0;
       % check if cur_point is always inside the bound
       for t = 0:n-1
           vec1(1:2) = cur_point - Quad{t+1};
           vec2(1:2) = Quad{mod(t+1,n)+1} - Quad{t+1};
           temp = cross(vec1,vec2);
           if temp(3) < 0
               satis = satis + 1;
           end
       end
       if satis == n
           [t, s] = map_quad2rect(cur_point,Quad,[h,w]);
           queries = [queries [t; s]];
           mask(i,j) = 1;
       end
   end
end
% go find values in original pic
Vq = interp2([1:h],[1:w],double(img(:,:,1)),queries(2,:),queries(1,:));
% fill it in Quad
for i = floor(y_sort(1)):ceil(y_sort(n))
   for j = floor(x_sort(1)):ceil(x_sort(n))
       if mask(i,j) == 1
          mask(i,j) = Vq(1);
          Vq(1) = [];
       end
   end
end
toc
end
function [i, j] = map_quad2rect( point,Quad,RectSize )
%mapping point in Quad to Rect
%   if not in Quad, return [-1,-1]

a = Quad{1};
b = Quad{2};
c = Quad{3};
d = Quad{4};

V_pa = a-point;
% for t direction(a to d)
V_ad = d-a;
V_bc = c-b;
V_ba = a-b;
% for s direction(a to b)
V_ab = b-a;
V_dc = c-d;
V_da = a-d;
% calculate t
A = -V_ad(1)*V_bc(2)+V_ad(2)*V_bc(1);
B = V_ad(1)*V_ba(2)-V_ad(2)*V_ba(1)+(V_ad(2)-V_bc(2))*V_pa(1)-(V_ad(1)-V_bc(1))*V_pa(2);
C = V_pa(1)*V_ba(2)-V_pa(2)*V_ba(1);
t1 = (-B+sqrt(B^2-4*A*C))/(2*A);
t2 = (-B-sqrt(B^2-4*A*C))/(2*A);
if t1<=1 && t1>=0
    t = t1;
elseif t2<=1 && t2>=0
    t = t2;
else
    t = -1;
end
%s_fromt = (V_pa+t*V_ad)./(V_ba+t*(V_ad-V_bc));
% calculate s
D = -V_ab(1)*V_dc(2)+V_ab(2)*V_dc(1);
E = V_ab(1)*V_da(2)-V_ab(2)*V_da(1)+(V_ab(2)-V_dc(2))*V_pa(1)-(V_ab(1)-V_dc(1))*V_pa(2);
F = V_pa(1)*V_da(2)-V_pa(2)*V_da(1);
s1 = (-E+sqrt(E^2-4*D*F))/(2*D);
s2 = (-E-sqrt(E^2-4*D*F))/(2*D);
if s1<=1 && s1>=0
    s = s1;
elseif s2<=1 && s2>=0
    s = s2;
else
    s = -1;
end
%t_froms = (V_pa+s*V_ab)./(V_da+s*(V_ab-V_dc));

i = 1 + s*(RectSize(1)-1);
j = 1 + t*(RectSize(2)-1);

end


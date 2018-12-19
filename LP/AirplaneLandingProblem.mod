var x1>=0;
var x2>=0;
var x3>=0;
var x4>=0;
var x5>=0;
var d>=0;

maximize z:d;

s.t. con1:x1-x2+d<=0;
s.t. con2:x2-x3+d<=0;
s.t. con3:x3-x4+d<=0;
s.t. con4:x4-x5+d<=0;
s.t. con5:x1>=1;
s.t. con6:x1<=2;
s.t. con7:x2>=3;
s.t. con8:x2<=4;
s.t. con9:x3>=5;
s.t. con10:x3<=6;
s.t. con11:x4>=7;
s.t. con12:x4<=8;
s.t. con13:x5>=9;
s.t. con14:x5<=10;
end;


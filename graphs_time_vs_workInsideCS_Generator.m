A = importdata('mutex_lock_-c.txt');
B = importdata('spin_lock_-c.txt');
C = importdata('my_spinTAS_lock_-c.txt');
D = importdata('my_mutex_lock_-c.txt');
E = importdata('my_spinTTAS_lock_-c.txt');
F = importdata('my_queue_lock_-c.txt');

a=A';
b=B';
c=C';
d=D';
e=E';
f=F';
x1=0:10:100;

figure('Color',[0.8 0.8 0.8]);
%p = polyfit(x,a,1);
%y1 = polyval(p,x);

plot(x1,a,'-o','Color','red');
hold on

grid minor
ax = gca;
ax.XMinorGrid = 'off';
set(gca,'FontSize',15);

title('Time vs WorkInsideCS','FontSize',20);
ylabel('time(ms)','FontSize',20);
xlabel('WorkInsideCS','FontSize',20);
ylim([0 4000]);
xlim([0 100]);

plot(x1,b,'-o','Color','black');
plot(x1,c,'-o','Color','magenta');
plot(x1,d,'-o','Color','cyan');
plot(x1,e,'-o','Color','green');
plot(x1,f,'-o','Color','blue');

l = legend('pthr mutex','pthr spin','mySpinTAS','mySpinTTAS','myMutex','myQueue','Location','southeastoutside');
set(l,'FontSize',20);

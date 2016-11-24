A = importdata('mutex_lock_-t.txt');
B = importdata('spin_lock_-t.txt');
C = importdata('my_mutex_lock_-t.txt');
D = importdata('my_spinTAS_lock_-t.txt');
E = importdata('my_spinTTAS_lock_-t.txt');
F = importdata('my_queue_lock_-t.txt');

a=A';
b=B';
c=C';
d=D';
e=E';
f=F';
x1=1:16;
x2=1:8;

figure('Color',[0.8 0.8 0.8]);
%p = polyfit(x,a,1);
%y1 = polyval(p,x);

plot(x1,a,'-o','Color','red');
hold on

grid minor
ax = gca;
ax.XMinorGrid = 'off';
set(gca,'FontSize',15);

title('Time vs Number of Threads','FontSize',20);
ylabel('time(ms)','FontSize',20);
xlabel('number of threads','FontSize',20);
ylim([0 9000]);
xlim([1 16]);

plot(x1,b,'-o','Color','black');
plot(x1,c,'-o','Color','magenta');
plot(x1,d,'-o','Color','cyan');
plot(x1,e,'-o','Color','green');
plot(x2,f,'-o','Color','blue');

l = legend('pthr mutex','pthr spin','myMutex','mySpinTAS','mySpinTTAS','myQueue','Location','southeastoutside');
set(l,'FontSize',20);

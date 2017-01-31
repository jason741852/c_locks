A = importdata('Time_data/mutex_lock_-o.txt');
B = importdata('Time_data/spin_lock_-o.txt');
C = importdata('Time_data/my_mutex_lock_-o.txt');
D = importdata('Time_data/my_spinTAS_lock_-o.txt');
E = importdata('Time_data/my_spinTTAS_lock_-o.txt');
F = importdata('Time_data/my_queue_lock_-o.txt');

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

title('Time vs WorkOutsideCS','FontSize',20);
ylabel('time(ms)','FontSize',20);
xlabel('WorkOutsideCS','FontSize',20);
ylim([0 1400]);
xlim([0 100]);

plot(x1,b,'-o','Color','black');
plot(x1,c,'-o','Color','magenta');
plot(x1,d,'-o','Color','cyan');
plot(x1,e,'-o','Color','green');
plot(x1,f,'-o','Color','blue');

l = legend('pthr mutex','pthr spin','myMutex','mySpinTAS','mySpinTTAS','myQueue','Location','southeastoutside');
set(l,'FontSize',20);

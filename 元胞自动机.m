% 参数
vmax = 10; % 最大速度
p = 0.6; % 原始数据0.8，慢化概率
road_length = 1000; % 道路长度
simulation_steps = 1000; % 仿真步数
render_on = 0; % 是否渲染
pause_on = 0; % 是否暂停
delay_on = 0; % 是否延迟
delay_length = 0.02; % 10 FPS

road = zeros(1, road_length); % 道路占用状态
road_next = road;
velocities = zeros(1, road_length); % 速度状态
velocities_next = velocities;

% 采样
num_samples = 2000;
samples = zeros(2, num_samples); % 密度和流量率
density_step = 1 / num_samples;

history = zeros(simulation_steps, road_length);
velocity_history = zeros(simulation_steps, road_length);

figure

for g = 1:num_samples
% 生成交通流
road = zeros(1, road_length); % 道路占用状态
road_next = road;
density = g / num_samples;
% 生成交通流
for i = 1:road_length
if rand < density
road(i) = 1;
end
end
if render_on
imshow(road);
drawnow
end
% 运行仿真
for i = 1:simulation_steps
history(i, :) = road;
velocity_history(i, :) = velocities;
%--------------------速度更新------------------------%
for j = 1:road_length
if road(j) == 1
distance = 0;
% 寻找最大速度的距离
bf = 0;
for k = 1:vmax
distance = k;
if j + k <= road_length % 索引是“考虑的单元格” - 是否安全着陆？
index = j + k;
else
index = j + k - road_length; % 处理环绕
end
if road(index) == 1
bf = 1;
end
if bf == 1, break, end
end
if velocities(j) < vmax % 加速
velocities(j) = velocities(j) + 1;
end
if (velocities(j) > distance - 1) && bf == 1 % 避免碰撞
velocities(j) = distance - 1;
end
if rand < p && velocities(j) > 0 % 随机减速
velocities(j) = velocities(j) - 1;
end
end
end
%--------------------运动------------------------%
for j = 1:road_length
if road(j) == 1
if j + velocities(j) <= road_length
index = j + velocities(j);
else
index = j + velocities(j) - road_length; % 处理环绕
end
% 碰撞检测
if road_next(index) == 1
disp('检测到碰撞')
end
road_next(index) = 1;
velocities_next(index) = velocities(j);
end
end
velocities = velocities_next;
road = road_next;
road_next = zeros(1, road_length);
if render_on
imshow(road);
drawnow
end
if pause_on
pause
end
if delay_on
pause(delay_length)
end
end
% 记录密度和流量率
velocity_history = velocity_history .* history;
samples(:, g) = [mean2(history) (sum(velocity_history(:)) / sum(history(:))) * mean2(history)];
disp('采样步骤:')
g
end

scatter(samples(1, :), samples(2, :));
axis([0 1 0 1]);
xlabel('密度')
ylabel('流量（归一化）')
title('流量-密度曲线')
# 导入必要的库  
import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
from matplotlib import pyplot as plt


# 定义LSTM网络模型
class LSTMNet(nn.Module):
    def __init__(self, input_size=1, hidden_size=50, output_size=1, num_layers=1):
        super(LSTMNet, self).__init__()
        # 定义LSTM层，输入大小为input_size，隐藏大小为hidden_size，层数为num_layers  
        self.lstm = nn.LSTM(input_size, hidden_size, num_layers, batch_first=True)
        # 定义全连接层，输入大小为hidden_size，输出大小为output_size  
        self.fc = nn.Linear(hidden_size, output_size)

    def forward(self, x):
        # 通过LSTM层进行前向传播  
        out, _ = self.lstm(x)
        # 取最后一个时间步的输出，通过全连接层得到最终预测值  
        out = self.fc(out[:, -1, :])
        return out

    # 创建LSTM网络模型实例


lstm_net = LSTMNet()

# 定义损失函数和优化器  
# 使用均方误差损失函数  
loss_func = nn.MSELoss()
# 使用Adam优化器，学习率为0.01  
optimizer = optim.Adam(lstm_net.parameters(), lr=0.01)

if __name__ == '__main__':
    # 创建训练数据，数据范围为0到2*pi之间，共100个数据点  
    x_train = np.linspace(0, 2 * np.pi, 100)
    # 创建标签数据，使用sin函数对训练数据进行映射  
    y_train = np.sin(x_train)
    # 将一维的x_train和y_train转换为三维张量，以适应LSTM的输入要求  
    x_train = x_train.reshape(-1, 1, 1)  # LSTM输入需要三维张量，第一维为序列长度，第二维为批次大小，第三维为输入特征的数量  
    y_train = y_train.reshape(-1, 1)

    # 将numpy数组转换为torch张量  
    x_train = torch.Tensor(x_train)
    y_train = torch.Tensor(y_train)

    # 训练模型  
    for epoch in range(10000):
        optimizer.zero_grad()  # 清零梯度  
        outputs = lstm_net(x_train)  # 前向传播计算输出  
        loss = loss_func(outputs, y_train)  # 计算损失  
        loss.backward()  # 反向传播计算梯度  
        optimizer.step()  # 更新权重  
        loss_val = loss.item()  # 获取当前epoch的损失值
        if loss_val < 0.00001:  # 当损失函数值小于1e-8时，停止训练
            break
        # 每100个epoch打印一次损失值  
        if epoch % 100 == 0:
            print(f'Epoch [{epoch + 1}/10000], Loss: {loss_val:.6f}')

            # 使用训练数据进行预测（在训练过程中使用的数据）
    with torch.no_grad():  # 不需要计算梯度，进行前向传播得到预测值  
        predicted_y_train = lstm_net(x_train)

        # 将torch张量转换回numpy数组，并去掉batch维度（如果有的话）
    x_train = x_train.squeeze().numpy()
    y_train = y_train.squeeze().numpy()
    predicted_y_train = predicted_y_train.squeeze().numpy()

    # 使用matplotlib绘制真实值和预测值  
    plt.plot(x_train, y_train, label='sin(x) (Ground Truth)')  # 真实值  
    plt.plot(x_train, predicted_y_train, label='predicted sin(x)', linestyle='--')  # 预测值  
    plt.legend()  # 添加图例  
    plt.show()  # 显示图形
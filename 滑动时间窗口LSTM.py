import numpy as np
import pandas as pd
from keras.models import Sequential
from keras.layers import LSTM, Dense
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt

# 设置随机数种子
np.random.seed(42)

# 读取Excel文件
df = pd.read_excel('C:\\Users\\w916\\Desktop\\HtbJEt9Nb655e46bebfa2a66ec63f940e2da156b\\result_data.xlsx',
                   usecols=[1], header=0)  # header=0表示第一行是标题行

# 提取索引和值作为numpy数组
values_to_predict = df.iloc[1:].values  # 从第二行开始取值，即去掉标题行
index = np.arange(1, len(values_to_predict) + 1)

# 生成sin(x)值
t = index

# 定义滑动窗口的大小
n = 5

# 准备序列数据
X = []
y = []
for i in range(n, len(t)):
    X_window = t[i - n:i].reshape(1, n, 1)  # 取最近的n个sin(x)值作为输入序列
    y_value = values_to_predict[i]  # Excel中对应的值作为标签
    X.append(X_window)
    y.append(y_value)
X = np.concatenate(X, axis=0)
y = np.array(y)

# 确保有足够的数据点用于训练和测试
assert len(X) >= n, "Not enough data points for the given window size."

# 划分训练集和测试集（不使用随机性，直接按照索引划分）
train_size = int(0.9 * len(X))
test_size = len(X) - train_size
X_train, y_train = X[:train_size], y[:train_size]
X_test, y_test = X[train_size:], y[train_size:]

# 构建LSTM模型3
model = Sequential()
model.add(LSTM(50, input_shape=(n, 1)))  # 输入形状为(n, 1)，LSTM层有50个单元
model.add(Dense(1))  # 输出层，预测Excel中的值
model.compile(optimizer='adam', loss='mse')  # 使用均方误差作为损失函数

# 训练模型
model.fit(X_train, y_train, epochs=5000, batch_size=32, verbose=1)

# 预测测试集
y_pred = model.predict(X_test)

# 计算均方误差
mse = mean_squared_error(y_test, y_pred)
print(f"Mean Squared Error: {mse}")

# 绘制真实值和预测值的比较图
plt.figure(figsize=(10, 6))
plt.plot(range(train_size, len(X)), y_test, label='True Values', marker='o')
plt.plot(range(train_size, len(X)), y_pred.flatten(), label='Predictions', linestyle='--', marker='x')
plt.title('True vs Predicted Values from Excel')
plt.xlabel('Sample Index')
plt.ylabel('Value from Excel')
plt.legend()
plt.grid(True)
plt.show()

import random
import time
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = ['SimHei']  # 使用中文黑体字体
plt.rcParams['axes.unicode_minus'] = False		# 显示负号
# 城市坐标
cities = {
    '长春': (125, 44),
    '武汉': (114, 31),
    '成都': (104, 31),
    '宁波': (122, 30),
    '郑州': (114, 35),
    '济南': (117, 37),
    '上海': (121, 31),
    '杭州': (120, 30),
    '芜湖': (118, 31),
    '昆明': (103, 25),
    '佛山': (113, 23),
    '西安': (109, 34),
    '天津': (117, 39),
    '北京': (116, 40),
    '广州': (113, 23),
    '长沙': (113, 28),
    '贵阳': (107, 27),
    '乌鲁木齐': (88, 44),
    '福州': (119, 26)
}


# 计算两点之间的距离
def distance(city1, city2):
    x1, y1 = cities[city1]
    x2, y2 = cities[city2]
    return ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5


# 计算路径长度
def total_distance(path):
    total = 0
    for i in range(len(path) - 1):
        total += distance(path[i], path[i + 1])
    total += distance(path[-1], path[0])  # 回到起点
    return total


# 生成初始种群
def generate_initial_population(size):
    population = []
    cities_list = list(cities.keys())
    for _ in range(size):
        path = cities_list[:]
        random.shuffle(path)
        population.append(path)
    return population


# 选择最优个体
def selection(population, k=5):
    return sorted(population, key=total_distance)[:k]


# 交叉
def crossover(parent1, parent2):
    start = random.randint(0, len(parent1) - 1)
    end = random.randint(start + 1, len(parent1))
    child = parent1[start:end] + [city for city in parent2 if city not in parent1[start:end]]
    return child


# 变异
def mutate(path):
    index1, index2 = random.sample(range(len(path)), 2)
    path[index1], path[index2] = path[index2], path[index1]
    return path


# 获取最短路径和距离的演化
def evolution_of_shortest_path(population_size, generations):
    start_time = time.time()
    shortest_distances = []
    shortest_path = None
    population = generate_initial_population(population_size)
    for gen in range(generations):
        parents = selection(population)
        next_generation = parents[:]
        while len(next_generation) < population_size:
            parent1, parent2 = random.choices(parents, k=2)
            child = crossover(parent1, parent2)
            if random.random() < 0.2:  # 20%的概率进行变异
                child = mutate(child)
            next_generation.append(child)
        population = next_generation
        best_path = selection(population, k=1)[0]
        shortest_path = best_path
        shortest_distance = total_distance(best_path)
        shortest_distances.append(shortest_distance)
    end_time = time.time()
    run_time = end_time - start_time
    return shortest_distances, run_time, shortest_path


# 生成最短距离与运行时间函数图
def plot_distance_time_evolution(population_size, generations):
    shortest_distances, run_time, best_path = evolution_of_shortest_path(population_size, generations)
    gens = list(range(1, generations + 1))

    plt.figure(figsize=(12, 6))

    # 绘制最短距离随代数的变化图
    plt.subplot(1, 2, 1)
    plt.plot(gens, shortest_distances, marker='o', linestyle='-')
    plt.xlabel('代数')
    plt.ylabel('最短距离')
    plt.title('最短距离时间变化曲线')

    # 绘制最短路径
    x_values = [cities[city][0] for city in best_path]
    y_values = [cities[city][1] for city in best_path]
    x_values.append(x_values[0])  # 回到起点
    y_values.append(y_values[0])

    plt.subplot(1, 2, 2)
    plt.plot(x_values, y_values, marker='o', linestyle='-')
    plt.xlabel('X坐标')
    plt.ylabel('Y坐标')
    plt.title('最短路径')

    plt.tight_layout()
    plt.show()


# 画出最短距离与运行时间函数图
plot_distance_time_evolution(population_size=100, generations=1000)

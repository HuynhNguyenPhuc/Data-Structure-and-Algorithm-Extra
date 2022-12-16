import random
for i in range(0,500000):
    num = random.randint(1,500000)
    with open('data.txt', 'a') as wf:
        wf.write(str(num) + ' ')
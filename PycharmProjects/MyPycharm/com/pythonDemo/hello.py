# for python test
import itertools
import time
from datetime import datetime

print("╔═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╤═╗")
print("║　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│  ║")
print('║　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　║')
print('║　│春│滟│江│空│江│江│人│不│白│谁│可│玉│此│鸿│昨│江│斜│不│　║')
print('║　│江│滟│流│里│天│畔│生│知│云│家│怜│户│时│雁│夜│水│月│知│　║')
print('║　│潮│随│宛│流│一│何│代│江│一│今│楼│帘│相│长│闲│流│沉│乘│　║')
print('║　│水│波│转│霜│色│人│代│月│片│夜│上│中│望│飞│潭│春│沉│月│　║')
print('║　│连│千│绕│不│无│初│无│待│去│扁│月│卷│不│光│梦│去│藏│几│　║')
print('║春│海│万│芳│觉│纤│见│穷│何│悠│舟│徘│不│相│不│落│欲│海│人│　║')
print('║江│平│里│甸│飞│尘│月│已│人│悠│子│徊│去│闻│度│花│尽│雾│归│　║')
print('║花│，│，│，│，│，│，│，│，│，│，│，│，│，│，│，│，│，│，│　║')
print('║月│海│何│月│汀│皎│江│江│但│青│何│应│捣│愿│鱼│可│江│碣│落│　║')
print('║夜│上│处│照│上│皎│月│月│见│枫│处│照│衣│逐│龙│怜│潭│石│月│　║')
print('║　│明│春│花│白│空│何│年│长│浦│相│离│砧│月│潜│春│落│潇│摇│　║')
print('║　│月│江│林│沙│中│年│年│江│上│思│人│上│华│跃│半│月│湘│情│　║')
print('║　│共│无│皆│看│孤│初│望│送│不│明│妆│拂│流│水│不│复│无│满│　║')
print('║　│潮│月│似│不│月│照│相│流│胜│月│镜│还│照│成│还│西│限│江│　║')
print('║　│生│明│霰│见│轮│人│似│水│愁│楼│台│来│君│文│家│斜│路│树│　║')
print('║　│。│。│。│。│。│？│。│。│。│？│。│。│。│。│。│。│。│。│　║')
print('║　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　║')
print('║　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　│　║')
print('╚═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╧═╝')

# time.time() 秒数
# time.localtime() 时间数组
timeStamp = time.time()
print(timeStamp)
print(time.localtime(timeStamp))

# 时间数组格式化
strTime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(timeStamp))
print(strTime)

# 字符串转换时间数组，时间数组格式化为字符串（可更改格式）
strT1 = time.strptime(strTime, "%Y-%m-%d %H:%M:%S")
strT2 = time.strftime("%Y/%m/%d %H:%M:%S", strT1)
print(strT1)
print(strT2)



url = r"http://image.baidu.com/search/acjson?tn=resultjson_com&ipn=rj&ct=201326592&fp=result&queryWord={word}&pn={pn}&rn=60"
u = (url.format(word="keyword", pn="serial"))
print(u)

for i in itertools.count(0,1):
    print(i)
    if i == 10:
        break

# for i in itertools.cycle("ABC"):
#     print(i)

for i in itertools.repeat("ABC",3):
    print(i)

# lambda 匿名函数
natuals = itertools.count(1,1)
ns = itertools.takewhile(lambda x: x <= 10, natuals)
list(ns)
print(list(ns))

# datetime
now = datetime.now()
print(now)

d = datetime.date(now)
print(d)

t = datetime.time(now)
print(t)
ll = str(t).split(".")
print(ll)
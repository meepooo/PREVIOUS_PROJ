from urllib import request #导入网页操作模块

from pip._vendor import requests


def test(a,b):
    print("%d" %(a+b))

# password = input("Input You Password Please:")
# print ('Your password is : %s' %password)
li = ["My","dog","is","lele"]
print (li)
print (li[-2])
srcstr="hello I am a great man"
list = srcstr.split(" ")
print(list)
print(list[-2])

test(2,5)

url = 'https://www.jd.com/'

resource = request.urlopen(url)

html = resource.read()

fn = open("page.html", "w+b") #'w'表示写, 'b'表示二进制

fn.write(html)

fn.close()

print("执行完毕")

if __name__ == "__main__":
    print("hello python")

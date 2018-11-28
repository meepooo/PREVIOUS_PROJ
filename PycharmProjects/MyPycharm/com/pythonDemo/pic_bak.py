#! /usr/bin/python
# -*- coding: utf-8 -*-
# FileName: pic.py
# Author: Lucky
# Date 2018/11/25

import requests
import re
import random
import itertools

def spiderPic(html, keyword, searchname):
    print("正在查找【"+ keyword +"】")
    if searchname=="baidu":
        urlword = "objURL"
    elif searchname=="baidusimp":
        urlword = "middleURL"
    else:
        return
    part = '"'+ urlword + '":"(.*?)"'

    for addr in re.findall(part, html, re.S):
        # print("正在爬取url:" + str(addr)[0:30] + "......")
        print("正在爬取url:" + addr)
        try:
            pics = requests.get(addr,timeout=10) #请求图像URL超时时间

            if str(pics.content).find("403 Forbidden")>0:
                print(str(pics.content))
                print(str(pics.content).find("403 Forbidden"))
                continue
        except requests.exception.ConnectError:
            print("URL地址错误")
            continue

        fq = open("F:\\sublime\\img\\美女\\" + str(random.randrange(0,1000,1))+".jpg","w+b")
        fq.write(pics.content)
        fq.close()

def baidusearchsimp(word):
        result = requests.get("http://image.baidu.com/search/index?tn=baiduimage&ps=1&ct=201326592&lm=-1&cl=2&nc=1&word=" + word)
        print(result)
        spiderPic(result.text, word, "baidusimp")

def baidusearchsimptest(word):
    result = requests.get(
        "http://image.baidu.com/search/index?tn=baiduimage&ps=1&ct=201326592&lm=-1&cl=2&nc=1&word=" + word)
    print(result)

def baidusearch(word):
    while True:
        url = r"http://image.baidu.com/search/acjson?tn=resultjson_com&ipn=rj&ct=201326592&fp=result&queryWord={word}" \
              r"&cl=2&lm=-1&ie=utf-8&oe=utf-8&st=-1&ic=0&word={word}&face=0&istype=2nc=1&pn={pn}&rn=60"
        for x in itertools.count(start=0, step=30):
            urls = (url.format(word=word, pn=x))
            print(urls)
            result = requests.get(urls)
            spiderPic(result.text, word, "baidu")

def baidusearchtest(word):
    while True:
        url = r"http://image.baidu.com/search/acjson?tn=resultjson_com&ipn=rj&ct=201326592&fp=result&queryWord={word}" \
              r"&cl=2&lm=-1&ie=utf-8&oe=utf-8&st=-1&ic=0&word={word}&face=0&istype=2nc=1&pn={pn}&rn=60"

        for x in itertools.count(start=0, step=30):
            urls = (url.format(word=word, pn=x))
            print(urls)
            result = requests.get(urls)
            print(result.text)
            break
        break

#python 主方法
if __name__ == "__main__":
    print("hello python")
    word = input("输入关键字：")
    # baidusearchtest(word)
    # baidusearchsimp(word)
    baidusearch(word)
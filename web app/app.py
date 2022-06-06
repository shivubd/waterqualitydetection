# -*- coding: utf-8 -*-
"""
Created on Tue Apr 19 15:35:43 2022

@author: shiva
"""
import datetime
from re import template
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
import pandas as pd
from flask import Flask, render_template, request
import flask
from datetime import datetime,date,time
from pytz import timezone

slno = 0
dat = ''
time = ''
ph = 0.0
tur = 0.0
temp = 0.0
prep = ''

app = Flask(__name__)

@app.route('/')
def water_quality():
    global slno,dat,time,ph,tur,temp
    df = pd.read_csv(r'file.csv')
    df = df.apply(pd.to_numeric, errors='coerce')
    df = df.dropna()

    x_data = df[['ph', 'Turbidity']]
    y_data = df['Potability']

    x_train, x_test, y_train, y_test = train_test_split(x_data, y_data, test_size=0.2, shuffle=False)

    classifier = KNeighborsClassifier(n_neighbors=13)
    classifier.fit(x_train, y_train)

    predval = classifier.predict([[ph, tur]])
    predval = str(predval)
    if(predval=='[0.]'):
        pred = 'BAD'
    else:
        pred = 'GOOD'
    return render_template('website.html', slno=slno, date=dat, time=time, ph="{:.3f}".format(ph), tur="{:.3f}".format(tur), temp="{:.3f}".format(temp), pred='GOOD')

@app.route('/mobile/')
def mobile_route():
    global slno,dat,time,ph,tur,temp
    return str(slno)+' '+str(dat)+' '+str(time)+' '+"{:.3f}".format(ph)+' '+"{:.3f}".format(tur)+' '+"{:.3f}".format(temp)+' '+'GOOD'

@app.route('/post',methods=['POST'])
def post():
    global slno,dat,time,ph,tur,temp
    slno+=1
    dat = date.today()
    dat = dat.strftime("%d-%m-%Y")
    time = datetime.now(timezone("Asia/Kolkata")).strftime('%H:%M')
    message = flask.request.data
    message = message.decode()
    if len(message)==0:
        message = '99.9 99.9 99.9'
    message = message.split(' ')
    message = [float(x) for x in message]
    ph = message[0]
    tur = message[1]
    temp = message[2]
    return flask.Response(status=204) 

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')

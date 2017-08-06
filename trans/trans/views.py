from django.shortcuts import render, render_to_response

from django.contrib import auth

from django.http import HttpResponseRedirect
from django.template import RequestContext

from django.views.decorators.csrf import csrf_protect, csrf_exempt

from django.core.exceptions import ValidationError # this is for <model>.full_clean()


def ontransl(request,  given = "", translated = ""):
    return render(request, "translator.html", {'given': given, 'translated': translated })

def twork(request):
    return render(request, "textwork.html" , {'text': '', 'word': '', 'descr': ''})

###########################################
import socket
import sys

def tran(request):
    fortransl = request.POST.get('fortransl','').encode('utf-8')

    if fortransl == "" or fortransl.isspace() or fortransl.isdigit():
        return render(request, "translator.html", {'given': "", 'translated': ""})
    else:
        address = '192.168.10.101'
        port = 3800
        sock = socket.socket()
        sock.connect((address, port))
        sock.send(fortransl)
        translated = sock.recv(256)
        return render(request, "translator.html", {'given': fortransl, 'translated': translated})


def tworking(request):
    text = request.POST.get('text', '').encode('utf-8')
    word = request.POST.get('word', '').encode('utf-8')

    if word == "" or word.isspace() or word.isdigit():
        return render(request, "textwork.html", {'text': text, 'word': '', 'descr': ''})
    else:
        address = '192.168.10.101'
        port = 3711
        sock = socket.socket()
        sock.connect((address, port))
        sock.send(word)
        descr = sock.recv(256)
        return render(request, "textwork.html", {'text': text, 'word':word, 'descr':descr})
###############################################
def contact(request):
    return render(request, "contacts.html")

def about(request):
    return render(request, "index.html")
from django.shortcuts import render, render_to_response

from django.contrib import auth

from django.http import HttpResponseRedirect
from django.template import RequestContext

from django.views.decorators.csrf import csrf_protect, csrf_exempt
from django.contrib.auth.decorators import login_required

from django.core.exceptions import ValidationError # this is for <model>.full_clean()

from regis.forms import *

#############################################

import os
# -*- coding: utf-8 -*-

def exe(word,init): # call preftree.cpp
    exestr = "~/KRPR/trans/preftree"
    exestr += ' ' + word + ' ' + init
    os.system(exestr)
    return

def wordadd(word, trans, pos, descr):
    filetoken = r"/home/arman/KRPR/OnTran/" + "En-Ru" + r"/"
    filetoken +=   word[0].upper() + r".txt"

    fileFORadd = open(filetoken, "a")

    tempstr = ("=\n"+ "%" + word + "%\n"
        + "*" + trans + "*\n" + "^" + pos + "^\n"
        + "+" + descr + "+\n\n")

    fileFORadd.write(tempstr)
    fileFORadd.close()
    exe(word , word)
    return

#############################################
def thanx(request):
    return render(request, "thanx.html");
#############################################
def test(request):
    par = " World "
    return render(request,"test.html",{"par" : par})
######################################

def register(request):
    if request.method == 'POST':
        form = RegistrationForm(request.POST)
        if form.is_valid():
            user = Memb.objects.create_user(
                username=form.cleaned_data['username'],
                password=form.cleaned_data['password1'],
                email=form.cleaned_data['email']
            )
            #here logining after registration begins
            username = form.cleaned_data['username']
            password = form.cleaned_data['password1']
            user = auth.authenticate(username=username, password=password)
            if user is not None:
                auth.login(request, user)
            #here logining after registration ends
                return HttpResponseRedirect('/success')
        else:
            return render(request, 'register.html', {'form': form, 'error': False})
    return HttpResponseRedirect('/')

######################################

def start(request):
    user = auth.get_user(request)
    if user.is_authenticated:
        username = user.get_username()
        return  render(request, "perscab.html", {'username': username})
    form = RegistrationForm()
    return render(request, "register.html", {'form': form})

###########################################################

def my_login(request):
    username = request.POST.get('username1','')
    password = request.POST.get('password','')
    #^ returns data from template's textinput with the name
    # of the 1st param or returns the 2nd params ('')

    user = auth.authenticate(username=username,password=password)
    # ^takes 2 args(:username and password) and returns an User object
    # if the password corresponds to the username
    # else returns None
    # it's in django.contrib.auth

    if user is not None and user.is_active:
        # if the password is correct and the user is active
        auth.login(request, user)
        user = auth.get_user(request)
        username = user.get_username()
        return render(request,"perscab.html", {'username': username})
    if user is None:
        form = RegistrationForm()
        return render(request, "register.html",{'form':form, 'error': True })
    #if not user.is_active:
    #    return HttpResponseRedirect("here is to be a ref to a login page"
    #                                "with an error 'go to an admin' ")
    return

############################################################################


def perscab(request):
    user = auth.get_user(request)
    if user.is_authenticated:
        username = user.get_username()
        return render(request, "perscab.html", {'username': username})
    else:
        form = RegistrationForm()
        return render(request, "register.html", {'form': form})

#################################################################################

def logout_page(request):
    auth.logout(request)
    return HttpResponseRedirect('/')


#################################################################################

def process(request):
    word = request.POST.get(r'word', '').encode('utf-8')
    transl = request.POST.get(r'transl', '').encode('utf-8')
    pos = request.POST.get(r'pos', '').encode('utf-8')
    descr = request.POST.get(r'descr', '').encode('utf-8')
    wordadd(word, transl, pos, descr)
    return HttpResponseRedirect("/reglog")

def processpt(request):
    wordpt = request.POST.get(r'wordpt', '')
    init = request.POST.get(r'init', '')
    exe(wordpt, init)
    return HttpResponseRedirect("/reglog")
















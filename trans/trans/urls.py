"""trans URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.10/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin
from regis.views import *
from trans.views import *

urlpatterns = [
    #admin urls:
    url(r'^admin/', admin.site.urls),
    #regis urls:
    url(r"^register/",register),
    url(r"^success", thanx),
    url(r'^perscab', my_login),
    url(r"^reglog", start),
    url(r'logout/$',logout_page),
    url(r'^process$', process),
    url(r"^processpt$", processpt),
    #service urls:
    url(r"^$", ontransl),
    url(r"^tran$", tran),
    url(r"^twork$",twork),
    url(r"^tworking$",tworking),
    url(r"^contacts", contact),
    url(r"^about", about),
    #test urls:
    url(r"^test",test),
]

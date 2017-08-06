from __future__ import unicode_literals
from django.db import models
from django.contrib.auth.models import User

class Memb(User):
    def __str__(self):
        return u'%s' %self.username
    class Meta:
        ordering = ['id']

from django.contrib import admin
from regis.models import Memb


class MembAdmin(admin.ModelAdmin):
    list_display = ("id","username", 'password', 'email')
    search_fields = ("id", 'username',)

admin.site.register(Memb,MembAdmin)
from django import forms
from regis.models import Memb
from django.utils.translation import ugettext_lazy as _
import re



class RegistrationForm(forms.Form):
    username  = forms.RegexField(regex=r'^\w+$', widget=forms.TextInput(attrs=dict(required=True, max_length=30)), label=_("Login"), error_messages={ 'invalid': _("This value must contain only letters, numbers and underscores.") })
    email     = forms.EmailField(widget=forms.TextInput(attrs=dict(required=True, max_length=30)), label=_("E-mail"))
    password1 = forms.CharField(widget=forms.PasswordInput(attrs=dict(required=True, max_length=30, render_value=False)), label=_("Password"))
    password2 = forms.CharField(widget=forms.PasswordInput(attrs=dict(required=True, max_length=30, render_value=False)), label=_("Password (again)"))


    def clean_username(self):
        try:
            user = Memb.objects.get(username__iexact=self.cleaned_data['username'])
        except Memb.DoesNotExist:
            return self.cleaned_data['username']
        raise forms.ValidationError(_("The login already exists. Please try another one."))

    def clean(self):
        if 'password1' in self.cleaned_data and 'password2' in self.cleaned_data:
            if self.cleaned_data['password1'] != self.cleaned_data['password2']:
                raise forms.ValidationError(_("The two password fields did not match."))
        return self.cleaned_data
'''
class LoginForm(forms.Form):
    username = forms.CharField(widjet=forms.TextInput(attrs=dict(required=True,max_length=30, render_value=False)))#, label=_("Login"))
    password = forms.CharField(widjet=forms.PasswordInput(attrs=dic, required=True, max_length=30, render_value=False))#, label=_("Password"))

'''
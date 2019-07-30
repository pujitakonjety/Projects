from django import  forms


class Login(forms.Form):
    name = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs = {'class':'input  is-rounded mywidth is-small','placeholder':'enter name'})
    )
    password = forms.CharField(
        required = True,
        widget=forms.PasswordInput(attrs = {'class':'input  is-rounded mywidth is-small','placeholder':'enter password'})
    )

class Signup(forms.Form):
    first_name = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs = {'class':'input is-rounded mywidth','placeholder':'enter firstname'})
    )
    last_name = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs = {'class':'input is-rounded width','placeholder':'enter lastname'})
    )
    username = forms.CharField(
        required=True,
        widget=forms.TextInput(attrs = {'placeholder':'enter name'})
    )
    password = forms.CharField(
        required=True,
        widget=forms.PasswordInput(attrs = {'placeholder':'enter password'})
    )
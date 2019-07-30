from django.forms import ModelForm
from onlineapp.models import *
from django import forms

class Addcollege(ModelForm):
    class Meta:
        model = College
        fields = ['name','location','acronym','contact']
        widgets = {
            'name':forms.TextInput(attrs ={'class':'input is-rounded mywidth','placeholder':'enter name'}),
            'location': forms.TextInput(attrs={'class':'input is-rounded mywidth','placeholder':'enter location'}),
            'acronym':forms.TextInput(attrs ={'class':'input is-rounded mywidth','placeholder':'enter acronym'}),
            'contact':forms.TextInput(attrs={'class':'input is-rounded mywidth','placeholder':'enter contact'})
        }

class AddstudentDetails(ModelForm):
    class Meta:
        model = Student
        exclude = ['id','college','dob']
        fields = ['name','email','db_folder','dropped_out']
        widgets = {
            'name':forms.TextInput(attrs = {'class':'input is-rounded mywidth','placeholder':'enter name'}),
            'email':forms.TextInput(attrs = {'class':'input is-rounded mywidth','placeholder':'enter email'}),
            'db_folder':forms.TextInput(attrs={'class': 'input is-rounded mywidth', 'placeholder': 'enter db_folder'}),
        }

class Addstudentmarks(ModelForm):
    class Meta:
        model = MockTest1
        exclude = ['id','student']
        widgets = {
            'problem1':forms.TextInput(attrs = {'class':'input is-rounded mywidth','placeholder':'enter problem1 marks'}),
            'problem2': forms.TextInput(
                attrs={'class': 'input is-rounded mywidth', 'placeholder': 'enter problem2 marks'}),
            'problem3': forms.TextInput(
                attrs={'class': 'input is-rounded mywidth', 'placeholder': 'enter problem3 marks'}),
            'problem4': forms.TextInput(
                attrs={'class': 'input is-rounded mywidth', 'placeholder': 'enter problem4 marks'}),
            'total': forms.TextInput(
                attrs={'class': 'input is-rounded mywidth', 'placeholder': 'enter total marks'}),
        }
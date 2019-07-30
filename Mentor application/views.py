from django.http import HttpResponse
from onlineapp.models import *
from .forms import *

from django.shortcuts import render
from django.template.loader import render_to_string
# Create your views here.
def hello_world(request):
    return HttpResponse("hello pujita")

def hello(request):
    html = """<h1>hello pujitakonjety"""
    return HttpResponse(html)

def get_my_college(request):
    c = College.objects.values('name').filter(acronym = 'SVECW')
    return HttpResponse(c[0]['name'])

def get_all_colleges(request):
    c = College.objects.values('name','acronym')
    str = "<html><head><table border = 1>"
    for inp in c:
        str += "<tr><td>"+inp['name']+"</td>"+"<td>"+inp['acronym']+"</td></tr>"
    str+="</table></head></html"
    return HttpResponse(str)

def hello(request):
    return render(request,'hello.html')

def details(request):
    c = College.objects.values('name','id')
    data = dict()
    data['key'] = c
    return render(request,'details.html',context=data)

def find(request,id):
    s =  Student.objects.values('name','mocktest1__total').filter(college_id = id)
    data = dict()
    data['key'] = s
    return render(request,'find.html',context = data)


def fill_student_form(request):
    """
    if request.method == 'POST':
        form = StudentForm(request.POST)
        if form.is_valid():
            # process the data in form.cleaned_data as required
            # ...
            # redirect to a new URL:
            return HttpResponse('/thanks/')

    else:
        form = StudentForm()

    return render(request, 'studentform.html', {'form': form})
    """
    if request.method == 'POST':
        if request.POST.get('name') and request.POST.get('college'):
            student = StudentForm()
            student.name =  request.POST.get('name')
            student.college = request.POST.get('college')
            student.save()
            return render(request,'templates/studentform.html')
        return render(request, 'templates/studentform.html')
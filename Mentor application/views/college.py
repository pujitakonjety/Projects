from django.views import View
from onlineapp.models import *
from django.shortcuts import render
from onlineapp.forms import *
from django.shortcuts import *
from django.urls import resolve
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.models import User
from django.contrib.auth.mixins import LoginRequiredMixin
from rest_framework import permissions

from onlineapp.serializer import *
from rest_framework.decorators import api_view, permission_classes,authentication_classes
from rest_framework.views import APIView


from rest_framework.authentication import SessionAuthentication, BasicAuthentication ,TokenAuthentication
from rest_framework.permissions import IsAuthenticated
from rest_framework.response import Response

import logging


def logout_user(request):
    logout(request)
    return redirect('onlineapp:loginform')


class CollegeView(LoginRequiredMixin, View):
    login_url = '/login/'

    def get(self, request, *args, **kwargs):
        # user_permissions = Permission.objects.filter(user=request.user)
        user_permissions = request.user.get_all_permissions()
        colleges = College.objects.all()
        if kwargs:
            # colleges = get_list_or_404(College,**kwargs)
            if 'acronym' in kwargs:
                s = Student.objects.values('name', 'mocktest1__total', 'email', 'id').filter(
                    college__acronym=kwargs['acronym'])
                ids = College.objects.values('id').filter(acronym=kwargs['acronym'])
                id = ids[0]['id']
            else:
                s = Student.objects.values('name', 'mocktest1__total', 'email', 'id').filter(college_id=kwargs['id'])
                id = kwargs['id']
            return render(request,
                          'find.html',
                          context={
                              'college_details': id,
                              'key': s,
                              'title': 'students from {} | '.format(id),

                          })

        return render(
            request, "details.html",
            context={
                'key': colleges,
                'title': 'All colleges',
                'user_permissions': user_permissions
            }
        )


class Addcollegeview(View):
    def get(self, request, **kwargs):
        if resolve(request.path_info).url_name == 'deletecollegeview':
            College.objects.get(id=kwargs.get('id')).delete()
            return redirect('onlineapp:display')
        clg = Addcollege()

        if kwargs:
            college = get_object_or_404(College, **kwargs)
            clg = Addcollege(instance=college)
        return render(request, 'index.html', context={'form': clg})

    def post(self, request, **kwargs):
        if resolve(request.path_info).url_name == 'editcollegeview':
            clg = College.objects.get(id=kwargs.get('id'))
            form = Addcollege(request.POST, instance=clg)
            if form.is_valid():
                form.save()
                return redirect("onlineapp:display")
        clg = Addcollege(request.POST)
        if clg.is_valid():
            clg.save()
            return redirect("onlineapp:display")


class Addstudentview(View):
    def get(self, request, *args, **kwargs):

        if resolve(request.path_info).url_name == 'addstudentview':
            details = AddstudentDetails()
            marks = Addstudentmarks()
            return render(request, 'studentform.html', context={'form1': details, 'form2': marks})
        if resolve(request.path_info).url_name == 'deletestudentview':
            id = Student.objects.values('college__id').filter(id=kwargs.get('id'))
            clg_id = id[0]['college__id']
            MockTest1.objects.get(student_id=kwargs.get('id')).delete()
            Student.objects.get(id=kwargs.get('id')).delete()
            return redirect('onlineapp:details1_html', clg_id)
        if resolve(request.path_info).url_name == 'editstudentview':
            details = get_object_or_404(Student, **kwargs)
            marks = get_object_or_404(MockTest1, student_id=kwargs.get('id'))
            # details = Student.objects.filter(id = kwargs.get('id')).first
            # marks = MockTest1.objects.filter(student_id = kwargs.get('sid')).first()
            form1 = AddstudentDetails(instance=details)
            form2 = Addstudentmarks(instance=marks)
            return render(request, 'studentform.html', context={'form1': form1, 'form2': form2})

    def post(self, request, *args, **kwargs):
        if resolve(request.path_info).url_name == 'addstudentview':
            details = AddstudentDetails(request.POST)
            marks = Addstudentmarks(request.POST)
            s = Student(name=request.POST['name'], email=request.POST['email'], db_folder=request.POST['db_folder'],
                        college_id=kwargs.get('id'), dropped_out=bool(request.POST['dropped_out']))
            s.save()
            # if details.is_valid() and marks.is_valid():
            #     details.save()
            #     marks.save(commit = False)
            #     id = Student.objects.values('id').filter(name =request.POST['name'] )
            #     marks.fields['student'] = id[0]['id']
            #     marks.save()

            p = MockTest1(problem1=request.POST['problem1'], problem2=request.POST['problem2'],
                          problem3=request.POST['problem3'], problem4=request.POST['problem4'],
                          total=request.POST['total'], student_id=s.id)
            p.save()
            return redirect('onlineapp:details1_html', **kwargs)
        if resolve(request.path_info).url_name == 'editstudentview':
            details = AddstudentDetails(request.POST)
            marks = Addstudentmarks(request.POST)
            Student.objects.filter(id=kwargs.get('id')).update(name=request.POST['name'])
            id = Student.objects.values('college__id').filter(id=kwargs.get('id'))
            clg_id = id[0]['college__id']
            return redirect('onlineapp:details1_html', clg_id)


class LoginController(View):
    def get(self, request, **kwargs):
        if request.user.is_authenticated:
            return redirect("onlineapp:display")
        print("hiii")
        print("vdlklfk")
        form = Login()
        return render(request,
                      'login.html',
                      context={'form': form}
                      )

    def post(self, request, **kwargs):
        form = Login(request.POST)
        if form.is_valid():
            user = authenticate(request, username=form.cleaned_data['name'], password=form.cleaned_data['password'])
        if user is not None:
            login(request, user)
            return redirect('onlineapp:display')
        return HttpResponse("error")


class SignupController(View):
    def get(self, request, **kwargs):
        form = Signup()
        return render(request,
                      'signupform.html',
                      context={'form': form}
                      )

    def post(self, request, **kwargs):
        form = Signup(request.POST)
        if form.is_valid():
            user = User.objects.create_user(**form.cleaned_data)
            user.save()
        if user is not None:
            login(request, user)
            return redirect('onlineapp:display')
        return HttpResponse("error")


@api_view(['GET', 'POST','PUT'])
@authentication_classes((SessionAuthentication, BasicAuthentication,TokenAuthentication))
@permission_classes((IsAuthenticated,))
@permission_classes((permissions.AllowAny,))
def addcollegeview(request):
    if request.method == "GET":
        college = College.objects.values('name', 'location', 'acronym', 'contact')
        serializer = CollegeSerializer(college, many=True)
        return Response(serializer.data)
    serializer = CollegeSerializer(data=request.data)
    if request.method == "POST":
        if serializer.is_valid():
            serializer.save()
            return Response({"message": "User created"})
        else:
            data = {
                "error": True,
                "errors": serializer.errors,
            }
            return Response(data)

@api_view(['POST'])
@permission_classes((permissions.AllowAny,))
def generate_tokens(request):
    for user in User.objects.all():
        Token.objects.get_or_create(user=user)
    x = 1

@api_view(['PUT'])
@permission_classes((permissions.AllowAny,))
def update_college(request,**kwargs):
    college = College.objects.get(id = kwargs['id'])
    serializer = CollegeSerializer(college,data = request.data)
    if serializer.is_valid():
        serializer.save()
        return Response({"message": "User updated"})
    else:
        data = {
            "error": True,
            "errors": serializer.errors,
        }
        return Response(data)

class getstudentsview(APIView):
    permission_classes = (permissions.AllowAny, )
    def get(self, request, *args, **kwargs):
        students = Student.objects.values('name', 'dob', 'email', 'db_folder', 'dropped_out','college_id').filter(
            college_id=kwargs.get('id'))
        serializer = StudentSerializer(students, many=True)
        return Response(serializer.data)
    def post(self,request,*args,**kwargs):
        serializer = StudentMarksSerializer(data=request.data,context={'cId':kwargs.get('id')})
        if serializer.is_valid():
            serializer.save()
            return Response({"message": "Student record created"})
        else:
            data = {
                "error": True,
                "errors": serializer.errors,
            }
            return Response(data)



class studentview(APIView):
    permission_classes = (permissions.AllowAny,)
    def get(self,request,**kwargs):
        student = Student.objects.values('name','dob','email','db_folder','dropped_out','college_id').filter(id = kwargs.get('sid'))
        serializer = StudentSerializer(student,many = True)
        return Response(serializer.data)
    def put(self,request,**kwargs):
        student = Student.objects.values('name','dob','email','db_folder','dropped_out','college_id').filter(id = kwargs.get('sid'))
        serializer = StudentMarksSerializer(student,data = request.data,context={'sid':kwargs.get('sid')})
        if serializer.is_valid():
            serializer.save()
            return Response({"message": "Student record created"})
        else:
            data = {
                "error": True,
                "errors": serializer.errors,
            }
            return Response(data)
def test(request):
    "sffffwfewa"

    return HttpResponse("my test view")



from django.urls import path
from onlineapp.views import *
from . import views

app_name = 'onlineapp'
urlpatterns = [
    # path('get_my_college',views.get_my_college),
    # path('get_all_colleges',views.get_all_colleges),
    # path('hello',views.hello),
    # path('details',views.details),
    # path('clg_student_id/<int:id>',views.find),
    # path('student_form',views.fill_student_form)
    path('test/',test),
    path('api/v1/token',generate_tokens),
    path('api/v1/colleges/', addcollegeview),
    path('api/v1/college/<int:id>/', getstudentsview.as_view(), name="studentslist"),
    path('api/v1/college/<int:id>/students/<int:sid>',studentview.as_view(),name = "studentdetails"),
    path('api/v1/college/<int:id>',update_college,name = "updatecollege"),
    path('colleges/add/', Addcollegeview.as_view(), name="addcollegeview"),
    path('colleges/<int:id>/edit', Addcollegeview.as_view(), name="editcollegeview"),
    path('colleges/<int:id>/delete', Addcollegeview.as_view(), name="deletecollegeview"),
    path('colleges/', CollegeView.as_view(), name="display"),
    path('colleges/<int:id>/', CollegeView.as_view(), name="details1_html"),
    path('colleges/<str:acronym>/', CollegeView.as_view(), name="marks"),
    path('student/<int:id>/add', Addstudentview.as_view(), name="addstudentview"),
    path('student/<int:id>/delete', Addstudentview.as_view(), name="deletestudentview"),
    path('student/<int:id>/edit', Addstudentview.as_view(), name="editstudentview"),
    path('login/', LoginController.as_view(), name='loginform'),
    path('signup/', SignupController.as_view(), name='signupform'),
    path('logout/', logout_user, name='logout')

]

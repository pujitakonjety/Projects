from rest_framework import serializers
from onlineapp.models import *


class CollegeSerializer(serializers.ModelSerializer):
    class Meta:
        model = College
        fields = ('name', "location", "acronym", "contact")



class StudentSerializer(serializers.ModelSerializer):
    class Meta:
        model = Student
        fields = ('id','name','dob','email','db_folder','dropped_out','college_id')

class MocktestSerializer(serializers.ModelSerializer):
    class Meta:
        model = MockTest1
        fields = ('id',  'problem1','problem2','problem3','problem4','total','student_id')


class StudentMarksSerializer(serializers.ModelSerializer):
    mocktest1 = MocktestSerializer(many=False, read_only=False)

    class Meta:
        model = Student
        fields = ('id', 'name', 'dob', 'email', 'db_folder', 'dropped_out', 'college_id', 'mocktest1')

    def create(self, validated_data):
        mocktest1 = validated_data.pop("mocktest1")
        stu = Student.objects.create(college_id=self.context['cId'], **validated_data)
        MockTest1.objects.create(student=stu, **mocktest1)
        return stu

    def update(self, instance, validated_data):
        mocktest1 = validated_data.pop("mocktest1")
        instance.update(**validated_data)
        mocktest1.student_id = self.context['sid']
        MockTest1.objects.update(**mocktest1)
        return instance

from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse
import subprocess as sub

from calculator.forms import VectorForm

# Create your views here.
def index(request):
    return render(request, 'calculator/index.html')

def vector(request):
    form = VectorForm() 

    return render(request, 'calculator/vector.html') 

def vector_api(request):
    x1 = float(request.GET.get('x1'))
    y1 = float(request.GET.get('y1'))
    x2 = float(request.GET.get('x2'))
    y2 = float(request.GET.get('y2'))
    
    output = "({0}, {1}) and ({2}, {3})".format(x1, y1, x2, y2)

    return HttpResponse(output)

def help(request):
    return HttpResponse("Hi, welcome to the help page.")

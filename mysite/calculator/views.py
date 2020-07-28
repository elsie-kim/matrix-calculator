from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse
from django.contrib import messages
import subprocess, os

from calculator.forms import VectorForm

# Create your views here.
def index(request):
    return render(request, 'calculator/index.html')

def vector(request):
    form = VectorForm(request.GET or None)
    answer = "None"
    
    try:
        x1 = str(form['x1'].value())
        y1 = str(form['y1'].value())
        x2 = str(form['x2'].value())
        y2 = str(form['y2'].value())
        operation = form['operation'].value()

        os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")
        input_cmd = ["./a.out", "-v", operation, "-v1", x1, y1, "-v2", x2, y2]
        answer = subprocess.check_output(input_cmd)
        print(float(answer))
        
        messages.add_message(request, messages.INFO, "Answer: " + str(float(answer)))
        
    except:
        print("Fields empty") 
    
    return render(request, 'calculator/vector.html', context = {'form':form}) 

def vector_api(request):
    #x1 = request.GET.get('x1')
    #y1 = request.GET.get('y1')
    #x2 = request.GET.get('x2')
    #y2 = request.GET.get('y2')
    #operation = request.GET.get('operation')

    #os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")
    
    #operation?
    #input_cmd = ["./a.out", "-v", operation, "-v1", x1, y1, "-v2", x2, y2]
    ##subproc = subprocess.Popen(output, stdout=subprocess.PIPE)
    #answer = subprocess.check_output(input_cmd)


    return HttpResponse("Hi")

def help(request):
    return HttpResponse("Hi, welcome to the help page.")

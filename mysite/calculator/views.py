from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, JsonResponse
from django.contrib import messages
import subprocess, os

from .forms import VectorForm, MatrixForm, SingleMatrixForm
from .utils.vector_utils import validate_vector_v, format_input_v, format_output_v
from .utils.matrix_utils import validate_matrix_m, format_input_m, format_output_m
from .utils.single_matrix_utils import validate_matrix_sm, format_input_sm, format_output_sm

# Create your views here.
# Front page
def index(request):
    return render(request, 'calculator/index.html')

# Help page
def help(request):
    return HttpResponse("Hi, welcome to the help page.")

# Vector page
def vector(request):
    # handle when page is first accessed/reloaded
    try:
        form = VectorForm()
    except:
        pass

    context = {'form' : form}

    return render(request, 'calculator/vector.html', context)

def validate_vector(request):
#    # cleans up user input and determines if the user's input is useable
    # response to AJAX call sent by pressing "Enter"
   
        # getting user's inputs from "Vector 1" and "Vector 2"
    v1 = request.GET.get('v1')
    v2 = request.GET.get('v2')
    operation = request.GET.get('operation')
    
    data = validate_vector_v(v1, v2, operation)
 
    # send back for AJAX to handle
    return JsonResponse(data)

def calculate_vector(request):
    v1 = request.GET.get('v1')
    v2 = request.GET.get('v2')
    operation = request.GET.get('operation')
    
    input_cmd = format_input_v(v1, v2, operation)
    
    os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")

    answer = format_output_v(subprocess.check_output(input_cmd))

    data = {
        'answer': answer
    }

    return JsonResponse(data)

# 'matrix/' page
def matrix(request):
    try:
        form = MatrixForm()
    except:
        pass

    context = {'form' : form}
    
    return render(request, 'calculator/matrix.html', context)

# determins whether user's input is useable or not
def validate_matrix(request):
    m1 = request.GET.get('m1')
    m2 = request.GET.get('m2')
    operation = request.GET.get('operation')

    data = validate_matrix_m(m1, m2, operation)
    
    return JsonResponse(data)

def calculate_matrix(request):
    m1 = request.GET.get('m1')
    m2 = request.GET.get('m2')
    operation = request.GET.get('operation')
    
    input_cmd = format_input_m(m1, m2, operation)
    print(input_cmd) 
    os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")

    out = subprocess.Popen(input_cmd, stdout=subprocess.PIPE)
    output = out.stdout.readlines()
    
    answer = format_output_m(output)

    data = {
        'answer': answer,
    }
    
    return JsonResponse(data)

def single_matrix(request):
    try:
        form = SingleMatrixForm()

    except:
        pass

    context = {'form': form}

    return render(request, 'calculator/single_matrix.html', context)

def validate_single_matrix(request):
    m = request.GET.get('m')
    operation = request.GET.get('operation')

    data = validate_matrix_sm(m, operation)

    return JsonResponse(data)

def calculate_single_matrix(request):
    m = request.GET.get('m')
    operation = request.GET.get('operation')

    input_cmd = format_input_sm(m, operation)
    
    os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")

    out = subprocess.Popen(input_cmd, stdout=subprocess.PIPE)
    output = out.stdout.readlines()

    answer = format_output_sm(output)

    data = {
        'answer': answer,
    }

    return JsonResponse(data)


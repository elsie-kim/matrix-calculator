from django.shortcuts import render
from django.http import  JsonResponse
from django.contrib import messages
import subprocess, os

from .utils.vector_utils import validate_vector_v, format_input_v, format_output_v
from .utils.matrix_utils import validate_matrix_m, format_input_m, format_output_m
from .utils.single_matrix_utils import validate_matrix_sm, format_input_sm, format_output_sm

# Views

# '/' page
def index(request):
    return render(request, 'calculator/index.html')

# '/help/' page
def help(request):
    return render(request, 'calculator/help.html')

# '/vector/' page
def vector(request):
    try:
        form = request.GET
        v1 = form['v1']
        v2 = form['v2']
        operation = form['operation']

        context = {
            'v1': v1,
            'v2': v2,
            'operation': operation,
        }

    except:
        context = {}

    return render(request, 'calculator/vector.html', context)

# cleans up user input and determines if it is useable
def validate_vector(request):
    # getting user's inputs from "Vector A", "Vector B", and "Operation"
    v1 = request.GET.get('v1')
    v2 = request.GET.get('v2')
    operation = request.GET.get('operation')
    
    data = validate_vector_v(v1, v2, operation)
 
    # send back for AJAX calls to handle
    return JsonResponse(data)

# sends cleaned user input to c++ program to be calculated
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

# '/matrix/' page
def matrix(request):
    try:
        form = request.GET
        m1 = form['m1']
        m2 = form['m2']
        operation = form['operation']

        context = {
            'm1': m1,
            'm2': m2,
            'operation': operation,
        }

    except:
        context = {}
    
    return render(request, 'calculator/matrix.html', context)

# cleans up user input and determines if it is useable
def validate_matrix(request):
    m1 = request.GET.get('m1')
    m2 = request.GET.get('m2')
    operation = request.GET.get('operation')

    data = validate_matrix_m(m1, m2, operation)
    
    return JsonResponse(data)

# sends cleaned user input to c++ program to be calculated
def calculate_matrix(request):
    m1 = request.GET.get('m1')
    m2 = request.GET.get('m2')
    operation = request.GET.get('operation')
    
    input_cmd = format_input_m(m1, m2, operation)
    os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")

    out = subprocess.Popen(input_cmd, stdout=subprocess.PIPE)
    output = out.stdout.readlines()
    
    answer = format_output_m(output)

    data = {
        'answer': answer,
    }
    
    return JsonResponse(data)

# '/single-matrix/' page
def single_matrix(request):
    try:
        form = request.GET

        m = form['m']

        context = {
            'm': m,
        }

    except:
        context = {}

    return render(request, 'calculator/single_matrix.html', context)

# cleans user input and determines if it is usable
def validate_single_matrix(request):
    m = request.GET.get('m')

    data = validate_matrix_sm(m)
    return JsonResponse(data)

# sends cleaned user input to c++ program to be calculated
def calculate_single_matrix(request):
    m = request.GET.get('m')

    input_cmd = format_input_sm(m)
    os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")

    out = subprocess.Popen(input_cmd, stdout=subprocess.PIPE)
    output = out.stdout.readlines()

    answer = format_output_sm(output)

    data = {
        'answer': answer,
    }

    return JsonResponse(data)


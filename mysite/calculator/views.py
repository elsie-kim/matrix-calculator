from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, JsonResponse
from django.contrib import messages
import subprocess, os

from .forms import VectorForm, MatrixForm

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
    # cleans up user input and determines if the user's input is useable
    def validate_vector(v):
        # removing any white space at the beginning
        start = 0
        for i in v:
            if i == " ":
                start += 1
            else:
                break
        
        v = v[start:]
        
        # return empty list to indicate empty input
        if v == "":
            return ""

        elif v[0] == '(' and v[-1] == ')':
            # remove parentheses
            v_split = v[1:-1]
           
            # remove spaces
            v_split = v_split.split(' ')
            v_split_2 = "" 
            
            # remove commas and any non-numerical characters
            for i in v_split:
                x = i.split(',')
            
                for j in x:
                    try:
                        # finding non-numerical characters
                        j = float(j)
        
                        # add to new string which holds the "cleaned" input
                        v_split_2 += str(j) + " "
                
                    except:
                        if j != "":
                            return j
                        else:
                            pass
            # return list of components
            return v_split_2 

        else:
            pass
            # return empty list to indicate that the user's input is not useable
            return ""
    
    # response to AJAX call sent by pressing "Enter"
    try: #try/except necessary?
        # getting user's inputs from "Vector 1" and "Vector 2"
        v1 = request.GET['v1']
        v2 = request.GET['v2']
        operation = request.GET['operation']
 
        # receive "cleaned" or empty list
        v1_clean = validate_vector(v1)
        v2_clean = validate_vector(v2)
        
        # validate user input
        if v1_clean != "" and v2_clean != "" and len(v1_clean.split(" ")) == len(v2_clean.split(" ")):
            if operation == "1":
                if len(v1_clean.split(" ")) == 4:
                    is_valid = 1
                    message = ""
                else:
                    is_valid = 0
                    message = "The cross product is limited to 3D vectors"
            else:
                is_valid = 1
                message = ""

        else:
            is_valid = 0
            message = "Invalid input"
        
        data = {
            'is_valid': str(is_valid),
            'v1_clean': v1_clean,
            'v2_clean': v2_clean,
            'operation' : str(operation),
            'message': message,
        }

    except:
        pass
    
    # send back for AJAX to handle
    return JsonResponse(data)

def calculate_vector(request):
    v1 = request.GET['v1']
    v2 = request.GET['v2']
    operation = request.GET['operation']
    
    input_cmd = ['./a.out', '-v', operation, '-v1']

    def format_input(v1, v2):
        v1 = v1.split(" ")
        v2 = v2.split(" ")

        for i in v1: # fit into one loop?
            if i != "":
                input_cmd.append(i)
        
        input_cmd.append("-v2")

        for i in v2:
            if i != "":
                input_cmd.append(i)

    
    os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")
    format_input(v1, v2)

    answer = subprocess.check_output(input_cmd)

    # format as a scalar value if dot product
    if operation == "0":
        # return int if answer is int, float if answer is float 
        try:
            answer = str(int(answer))
        except:
            answer = str(float(answer))
    else:
        answer = str(answer)
        answer = answer[2:-3]

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

    m1_clean = ""
    m2_clean = ""

    # split chunk of text into lines
    m1_split = m1.splitlines()
    m2_split = m2.splitlines()

    is_valid = 2

    # split lines into individual components
    # and add "-n" to indicate a new line, so that main.cpp
    # can process the string and split into 2D vectors
    for i in range(len(m1_split)-1):
        x = m1_split[i].split()
        y = m1_split[i+1].split()

        a = [i.strip(" ") for i in x]
        b = [i.strip(" ") for i in y]

        if len(a) != len(b):
            is_valid = 0
            break

        else:
            is_valid = 1
   
    if (is_valid == 1):
        for i in range(len(m2_split)-1):
            x = m2_split[i].split()
            y = m2_split[i+1].split()

            a = [i.strip(" ") for i in x]
            b = [i.strip(" ") for i in y]


            if len(a) != len(b):
                is_valid = 0
                break
            else:
                is_valid = 1

        if (is_valid == 1):

            for i in m1.splitlines():
                m1_clean += "-n "
                for j in i:
                    try:
                        j = float(j)
                        m1_clean += str(j) + " "

                    except:
                        if j!= " ":
                            is_valid = 0
                            break

            for i in m2.splitlines():
                m2_clean += "-n "
                
                for j in i:
                    try:
                        j = float(j)
                        m2_clean += str(j) + " "
                    
                    except:
                        if j != " ":
                            is_valid = 0
                            break
    
    data = {
        'is_valid': is_valid,
        'm1': m1_clean,
        'm2': m2_clean,
#        'operation'
    }

    return JsonResponse(data)

def calculate_matrix(request):

    return HttpResponse("Hello")

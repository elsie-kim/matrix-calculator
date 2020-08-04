from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, JsonResponse
from django.contrib import messages
import subprocess, os

from .forms import VectorForm

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































































##def dimension(request):
##    dimension = int(request.GET.get('dimension'))
##
##    def not_valid(d):
##        if d > 0:
##            return False
##        return True
##
##    data = {
##            'not_valid': not_valid(dimension)
##    }
##    return JsonResponse(data)
#
## Vector Calculator ("vector/")
#def vector(request):
#    def valid_input(v):
#        # check that the components are surrounded by parentheses
#        if v == "":
#            return False
#        elif v[0] == '(' and v[-1] == ')':
#            # remove parentheses
#            v_split = v[1:-1]
#           
#            # remove spaces
#            v_split = v_split.split(' ')
#            v_split_2 = []
#             
#            for i in v_split:
#                x = i.split(',')
#            
#                for j in x:
#                    try:
#                        j = int(j)
#                        #v_split_2.append(j)
#                        
#                    except:
#                        return False
#            return True
#
#        else:
#            return False
#
#    vector = None
#    try:
#        vector = request.GET['vector']
#        print("step1")
#    except:
#        pass
#
#    if (vector):
#        print("step2")
#        print(valid_input(vector))
#
#        if not valid_input(vector):
#            def get_context_data(self, **kwargs):
#                context = super(VectorView, self).get_context_data(**kwargs)
#                context['is_valid'] = int(valid_input(vector))
#                return context
#            return 
#            
#             
#
#
#    #except:
#        #print("Hi")
#   # def parse_vector(v):
#
#   # 
#
#
#   # try: 
#   #     dimension = request.GET.get('dimension')
#   #     print(dimension)
#   # except:
#   #     print("Exception")
#    
#
#    #try:
#    #form = VectorForm() 
#
#    #except:
#    
#    #try:
#        #dimension = request.GET.get('dimension')
#        #print(dimension)
#    
#        #try: 
#            #form = VectorForm(request.GET or None)
#        
#            #x1 = str(form['x1'].value())
#            #y1 = str(form['y1'].value())
#            #x2 = str(form['x2'].value())
#            #y2 = str(form['y2'].value())
#            #operation = form['operation'].value()
#
#            #os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")
#            #input_cmd = ["./a.out", "-v", operation, "-v1", x1, y1, "-v2", x2, y2]
#            #answer = subprocess.check_output(input_cmd)
#            #print(float(answer))
#            
#            #messages.add_message(request, messages.INFO, "Answer: " + str(float(answer)))
#        #except:
#            #print("HIII")
#        
#    #except:
#        #print("Fields empty") 
#
#    return render(request, 'calculator/vector.html')
#
#def vector_landing(request):
#    dimension = request.GET['dimension']
#    print(dimension)
# 
#    return HttpResponse('')
#
#
#def vector_api(request):
#    #x1 = request.GET.get('x1')
#    #y1 = request.GET.get('y1')
#    #x2 = request.GET.get('x2')
#    #y2 = request.GET.get('y2')
#    #operation = request.GET.get('operation')
#
#    #os.chdir("/home/elsie/calculator/matrix-calculator/calc-c++/")
#    
#    #operation?
#    #input_cmd = ["./a.out", "-v", operation, "-v1", x1, y1, "-v2", x2, y2]
#    ##subproc = subprocess.Popen(output, stdout=subprocess.PIPE)
#    #answer = subprocess.check_output(input_cmd)
#
#
#    return HttpResponse("Hi")

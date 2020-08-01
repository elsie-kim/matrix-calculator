from django import forms
from django.utils.safestring import mark_safe


# Handles front-end input 
class VectorForm(forms.Form):
    vector1 = forms.CharField(initial='Ex. (a, b, c, ...)')
    vector2 = forms.CharField(initial='Ex. (a, b, c, ...)')
    OPERATION_LIST = [(-1, 'Dot Product'), (1, 'Cross Product')]
    operation = forms.ChoiceField(label='\nOperation:', choices=OPERATION_LIST) 














    

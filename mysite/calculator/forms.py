from django import forms
from django.utils.safestring import mark_safe

#from .models import Vector

class VectorForm(forms.Form):
    x1 = forms.IntegerField(label=mark_safe('x:'), required=True)
    y1 = forms.IntegerField(label=mark_safe('<br>y:'), required=True)
    x2 = forms.IntegerField(label=mark_safe('<br>x:'), required=True)
    y2 = forms.IntegerField(label=mark_safe('<br>y:'), required=True)
    
    OPERATION_LIST = [(0, 'Dot Product'), (1, 'Cross Product')]
    operation = forms.ChoiceField(label='\nOperation:', choices=OPERATION_LIST)

    

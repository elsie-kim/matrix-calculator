from django import forms

#from .models import Vector

class VectorForm(forms.Form):
    x1 = forms.IntegerField(required=True)
    y1 = forms.IntegerField(required=True)

    

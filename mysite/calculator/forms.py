from django import forms

# Handles front-end input 
class VectorForm(forms.Form):
    vector1 = forms.CharField(initial='Ex. (a, b, c, ...)')
    vector2 = forms.CharField(initial='Ex. (a, b, c, ...)')
    OPERATION_LIST = [(0, 'Dot Product'), (1, 'Cross Product')]
    operation = forms.ChoiceField(label='\nOperation:', choices=OPERATION_LIST) 

class MatrixForm(forms.Form):
    matrix1 = forms.CharField(widget=forms.Textarea, required=True)
    matrix2 = forms.CharField(widget=forms.Textarea, required=True)
    OPERATION_LIST = [(0, 'Multiplication'), (1, 'Addition'), (2, 'Subtraction')]
    operation = forms.ChoiceField(label='Operation:', choices=OPERATION_LIST)

class SingleMatrixForm(forms.Form):
    matrix = forms.CharField(widget=forms.Textarea)
    OPERATION_LIST = [(3, 'Reduced Row Echelon Form (Augmented)'), (4, 'Solve Matrix')]
    operation = forms.ChoiceField(label='Operation:', choices=OPERATION_LIST)










    

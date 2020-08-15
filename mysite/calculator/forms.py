from django import forms

# Handles front-end input 
class VectorForm(forms.Form):
    vector1 = forms.CharField(initial='Ex. (a, b, c, ...)')
    vector2 = forms.CharField(initial='Ex. (a, b, c, ...)')
    OPERATION_LIST = [(0, 'Dot Product'), (1, 'Cross Product')]
    operation = forms.ChoiceField(label='\nOperation:', choices=OPERATION_LIST) 

class MatrixForm(forms.Form):
    matrix1 = forms.CharField(widget=forms.Textarea)
    matrix2 = forms.CharField(widget=forms.Textarea, required=False)
    OPERATION_LIST = [(0, 'Multiplication'), (1, 'Reduced Row Echelon Form (Augmented)'), (2, 'Addition'), (3, 'Subtraction')]
    operation = forms.ChoiceField(label='Operation:', choices=OPERATION_LIST)












    

from django import forms

# Handles front-end input 
class VectorForm(forms.Form):
#    def __init__(self, *args, **kwargs):
#        super(VectorForm, self).__init__(*args, **kwargs)
#        self.fields['vector1'].widget = forms.TextInput(attrs={'class': 'form-control'})
#        self.fields['vector2'].widget = forms.TextInput(attrs={'class': 'form-control'})
#        self.fields['operation'].widget = forms.Select(attrs={'class': 'form-control'})

    vector1 = forms.CharField(widget=forms.TextInput(attrs={'class': 'form-control'}), label="A", initial='Ex. (a, b, c, ...)')
    vector2 = forms.CharField(widget=forms.TextInput(attrs={'class': 'form-control'}), label="B", initial='Ex. (a, b, c, ...)')
    OPERATION_LIST = [(0, 'Dot Product'), (1, 'Cross Product')]
    operation = forms.ChoiceField(label='Operation:', choices=OPERATION_LIST) 

class MatrixForm(forms.Form):
    matrix1 = forms.CharField(label="A: ", widget=forms.Textarea, required=True)
    matrix2 = forms.CharField(label="B: ", widget=forms.Textarea, required=True)
    OPERATION_LIST = [(0, 'Multiplication'), (1, 'Addition'), (2, 'Subtraction')]
    operation = forms.ChoiceField(label='Operation:', choices=OPERATION_LIST)

class SingleMatrixForm(forms.Form):
    matrix = forms.CharField(label="A: ", widget=forms.Textarea)
    OPERATION_LIST = [(3, 'Reduced Row Echelon Form (Augmented)')]
    operation = forms.ChoiceField(label='Operation:', choices=OPERATION_LIST)










    

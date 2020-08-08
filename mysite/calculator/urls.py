from django.urls import path

from . import views

urlpatterns = [
        path('', views.index, name='index'),
        path('vector/', views.vector, name='vector'),
        path('vector/validate/', views.validate_vector, name='validate_vector'),
        path('vector/calculate/', views.calculate_vector, name='calculate_vector'),
        path('matrix/', views.matrix, name='matrix'),
        path('matrix/validate/', views.validate_matrix, name='validate_matrix'),
        path('matrix/calculate/', views.calculate_matrix, name='calculate_matrix'),
        path('help/', views.help, name='help'),
]

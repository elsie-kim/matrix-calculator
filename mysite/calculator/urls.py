from django.urls import path

from . import views

urlpatterns = [
        path('', views.index, name='index'),
        path('vector/', views.vector, name='vector'),
        path('vectorapi', views.vector_api, name='vector_api'),
#        path('matrix/', views.matrix, name='matrix'),
        path('help/', views.help, name='help'),
]

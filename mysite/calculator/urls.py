from django.urls import path

from . import views

urlpatterns = [
        path('', views.index, name='index'),
        path('vector/', views.vector, name='vector'),
        path('vector/validate/', views.validate, name='validate'),
        path('help/', views.help, name='help'),
]

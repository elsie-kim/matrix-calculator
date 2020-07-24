from django.db import models

# Create your models here.
class Vector(models.Model):
    x1 = models.IntegerField()
    x2 = models.IntegerField()
    y1 = models.IntegerField()
    y2 = models.IntegerField()
    z1 = models.IntegerField()
    z2 = models.IntegerField()

    def __str__(self):
        return self.choice_text

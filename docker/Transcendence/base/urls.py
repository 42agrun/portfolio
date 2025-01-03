from django.urls import path
from . import views

urlpatterns = [
    path('login/', views.loginPage, name="login"),
    path('logout/', views.logoutUser, name="logout"),
    path('register/', views.registerPage, name="register"),

    path('', views.base, name="base"),
    path('home/', views.home, name="home"),
    path('pong/', views.pong, name="pong"),
    path('pong_4/', views.pong_4, name="pong_4"),
    path('pong_ai/', views.pong_ai, name="pong_ai"),
    path('pong_tournament_4/', views.pong_tournament_4, name="pong_tournament_4"),
    path('pong_tournament_8/', views.pong_tournament_8, name="pong_tournament_8"),
    path('pong_tournament_game_4/', views.pong_tournament_game_4, name="pong_tournament_game_4"),
    path('pong_tournament_game_8/', views.pong_tournament_game_8, name="pong_tournament_game_8"),
    path('pong_tournament_4_table/', views.pong_tournament_4_table, name="pong_tournament_4_table"),
    path('pong_tournament_8_table/', views.pong_tournament_8_table, name="pong_tournament_8_table"),
    path('games/', views.games, name="games"),
    path('ttt/', views.ttt, name="ttt"),
    path('ttt_ai/', views.ttt_ai, name="ttt_ai"),
    path('ttt_new/', views.ttt_new, name="ttt_new"),
    path('ttt_new_ai/', views.ttt_new_ai, name="ttt_new_ai"),
    path('profile/', views.profile, name="profile"),
    path('stats/', views.stats, name="stats"),
    path('edit_profile/', views.edit_profile, name="edit_profile"),
]

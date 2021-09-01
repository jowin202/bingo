#!/usr/bin/python3

import datetime
from flask_sqlalchemy import SQLAlchemy
from sqlalchemy.sql import func
from sqlalchemy import or_, and_
from flask import Flask
from flask import current_app, flash, jsonify, make_response, redirect, request, Response, url_for

import random



app = Flask(__name__)
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://johannes:abc123@localhost/bingo3' #change this
db = SQLAlchemy(app)


def resp(json, status = 0):
    msg = ""
    if status == 1:
        msg = "not found"
        json = []
    if status == 123:
        msg = "full"
    if status == 124:
        msg = "number already drawn"
        json = []
    if status == 125:
        msg = "numbers between 1 and 75"
        json = []
    if status == 404:
        msg = "not found"
        json = []
    if status == 405:
        msg = "method not allowed"
        json = []
    data = {'status': status, 'msg': msg, 'data': json}
    return jsonify(data), 200, {'Content-Type': 'application/json; charset=utf-8'}


def rand_group(a,b):
    group = []
    while len(group) < 5:
        x = random.randint(a,b)
        if x in group:
            continue
        else:
            group.append(x)
    return group


def randomize():
    return rand_group(1,15) + rand_group(16,30) + rand_group(31, 45) + rand_group(46,60) + rand_group(61,75)
    

class game(db.Model):
   game_id = db.Column(db.Integer, primary_key = True)
   game_name = db.Column( db.String(32))
   game_owner = db.Column(db.String(32))  
   description = db.Column(db.String(32))
   created = db.Column(db.DateTime, default=datetime.datetime.utcnow)
   
   def __init__(self, game_name, game_owner, description):
       self.game_name = game_name
       self.game_owner = game_owner
       self.description = description
   
   def toJson(self):
       return {'game_id': self.game_id, 'game_name': self.game_name, 'game_owner': self.game_owner, 'description': self.description}
   
   
class drawn_number(db.Model):
    num_id = db.Column(db.Integer, primary_key = True)
    game_id = db.Column(db.Integer, db.ForeignKey(game.game_id, ondelete='CASCADE', onupdate='CASCADE'), nullable=False)
    number = db.Column(db.Integer)
    created = db.Column(db.DateTime, default=datetime.datetime.utcnow)
    
    def __init__(self, game_id, num):
        self.game_id = game_id
        self.number = num

    
    
class board(db.Model):
    board_id = db.Column(db.Integer, primary_key = True)
    game_id = db.Column(db.Integer, db.ForeignKey(game.game_id, ondelete='CASCADE', onupdate='CASCADE'),  nullable=False)
    board_owner = db.Column(db.String(32))
    created = db.Column(db.DateTime, default=datetime.datetime.utcnow)
    b1 = db.Column(db.Integer)
    b2 = db.Column(db.Integer)
    b3 = db.Column(db.Integer)
    b4 = db.Column(db.Integer)
    b5 = db.Column(db.Integer)

    i1 = db.Column(db.Integer)
    i2 = db.Column(db.Integer)
    i3 = db.Column(db.Integer)
    i4 = db.Column(db.Integer)
    i5 = db.Column(db.Integer)
    
    n1 = db.Column(db.Integer)
    n2 = db.Column(db.Integer)
    n3 = db.Column(db.Integer)
    n4 = db.Column(db.Integer)
    n5 = db.Column(db.Integer)

    g1 = db.Column(db.Integer)
    g2 = db.Column(db.Integer)
    g3 = db.Column(db.Integer)
    g4 = db.Column(db.Integer)
    g5 = db.Column(db.Integer)

    o1 = db.Column(db.Integer)
    o2 = db.Column(db.Integer)
    o3 = db.Column(db.Integer)
    o4 = db.Column(db.Integer)
    o5 = db.Column(db.Integer)
    
    def __init__(self, game_id, board_owner, numbers):
        self.game_id = game_id
        self.board_owner = board_owner
        
        self.b1 = numbers[0]
        self.b2 = numbers[1]
        self.b3 = numbers[2]
        self.b4 = numbers[3]
        self.b5 = numbers[4]
        
        self.i1 = numbers[5]
        self.i2 = numbers[6]
        self.i3 = numbers[7]
        self.i4 = numbers[8]
        self.i5 = numbers[9]
        
        self.n1 = numbers[10]
        self.n2 = numbers[11]
        self.n3 = numbers[12]
        self.n4 = numbers[13]
        self.n5 = numbers[14]
        
        self.g1 = numbers[15]
        self.g2 = numbers[16]
        self.g3 = numbers[17]
        self.g4 = numbers[18]
        self.g5 = numbers[19]
        
        self.o1 = numbers[20]
        self.o2 = numbers[21]
        self.o3 = numbers[22]
        self.o4 = numbers[23]
        self.o5 = numbers[24]
        
        
    
    def toJson(self):
       nums = []
       nums.append(self.b1)
       nums.append(self.b2)
       nums.append(self.b3)
       nums.append(self.b4)
       nums.append(self.b5)
       
       nums.append(self.i1)
       nums.append(self.i2)
       nums.append(self.i3)
       nums.append(self.i4)
       nums.append(self.i5)
       
       nums.append(self.n1)
       nums.append(self.n2)
       nums.append(self.n3)
       nums.append(self.n4)
       nums.append(self.n5)
       
       nums.append(self.g1)
       nums.append(self.g2)
       nums.append(self.g3)
       nums.append(self.g4)
       nums.append(self.g5)
       
       nums.append(self.o1)
       nums.append(self.o2)
       nums.append(self.o3)
       nums.append(self.o4)
       nums.append(self.o5)
       return {'board_id': self.board_id, 'game_id': self.game_id, 'board_owner': self.board_owner, 'numbers':  nums}



db.create_all()

@app.route('/')
def hello():
    return "Hello World!"


@app.route('/game/')
def list_games():
    result = []
    for g in game.query.all():
        result.append(g.toJson())
    
    return resp(result)


@app.route('/game/new', methods=['PUT'])
def new_game():
    if request.method != "PUT":
        return resp(None, 405)

    content = request.json
    jsonify(content)
    
    
    new_game = game(content['name'],content['owner'],content['description'])
    db.session.add(new_game)
    db.session.commit()
    
    return resp(None, 200)





@app.route('/game/<int:gid>/', methods=['GET', 'DELETE', 'PUT'])
def list_or_delete_game(gid):
    if request.method == 'GET':
        res = game.query.get(gid)
        if res != None:
            res2 = drawn_number.query.filter_by(game_id=gid).all()
            nums = []
            for num in res2:
                nums.append(num.number)
            output = res.toJson()
            output['nums'] =  nums
            return resp(output)
        return resp(None, 1)
    elif request.method == 'DELETE':
        res = game.query.get(gid)
        if res != None:
            db.session.delete(res)
            db.session.commit()
            return resp(None, 200)
        return resp(None, 404)
    elif request.method == 'PUT':
        res = game.query.get(gid)
        content = request.json
        res.game_name = content['game_name']
        res.game_owner = content['game_owner']
        res.description = content['description']
        db.session.commit()
        return resp([])
        
@app.route('/game/<int:gid>/draw_random', methods=['GET'])
def draw_random_number(gid):
    res = drawn_number.query.filter_by(game_id=gid).all()
    if len(res) >= 75:
        return resp(None, 123)
    
    while True:
        a = random.randint(1,75)
        for number in res:
            if a == number.number:
                a = -1
                break
                

        if a != -1:
            break
        
    if a >= 0:
        new_number = drawn_number(gid,a)
        db.session.add(new_number)
        db.session.commit()
    elif a == -1:
        return resp(None, 123)
    return resp(None, 200)


        
@app.route('/game/<int:gid>/draw/<int:num>', methods=['PUT'])
def draw_number(gid, num):
    res = drawn_number.query.filter_by(game_id=gid).all()
    if len(res) >= 75:
        return resp(None, 123)
    
    if num < 1 or num > 75:
        return resp(None, 125)
    
    for number in res:
        if num == number.number:
            return resp(None, 124)
        

    new_number = drawn_number(gid, num)
    db.session.add(new_number)
    db.session.commit()
    return resp(None, 200)


@app.route('/game/<int:gid>/drawn/', methods=['GET'])
def get_drawn_number(gid):
    res = drawn_number.query.filter_by(game_id=gid).all()
    
    output = []
    for val in res:
        output.append(val.number)
    return resp(output, 200)



    
@app.route('/board/new', methods=['PUT'])
def new_board():
    if request.method != "PUT":
        return resp(None, 405)

    content = request.json
    jsonify(content)
    
    if 'numbers' in content.keys():
        new_board = board(content['game_id'],content['board_owner'],content['numbers'])
    else:
        new_board = board(content['game_id'],content['board_owner'],randomize())
    db.session.add(new_board)
    db.session.commit()
    
    return resp(None, 200)





@app.route('/game/<int:gid>/boards/')
def list_boards(gid):
    result = []
    for g in board.query.filter_by(game_id=gid).all():
        result.append(g.toJson())
    
    return resp(result)

@app.route('/board/<int:bid>/', methods=['GET', 'DELETE'])
def list_board(bid):
    if request.method == 'GET':
        res = board.query.filter_by(board_id=bid).first()
        if res != None:
            return resp(res.toJson())
        return resp(None, 1)
    elif request.method == 'DELETE':
        res = board.query.get(bid)
        if res != None:
            db.session.delete(res)
            db.session.commit()
            return resp(res.toJson())
        return resp(None, 1)



@app.route('/status/<int:gid>')
def boards_status(gid):
    res = db.session.query(board.board_id, func.count(board.board_id)).filter(and_(drawn_number.game_id == gid, board.game_id == gid, or_(board.b1 == drawn_number.number,board.b2 == drawn_number.number,board.b3 == drawn_number.number,board.b4 == drawn_number.number,board.b5 == drawn_number.number,board.i1 == drawn_number.number,board.i2 == drawn_number.number,board.i3 == drawn_number.number,board.i4 == drawn_number.number,board.i5 == drawn_number.number,board.n1 == drawn_number.number,board.n2 == drawn_number.number,board.n3 == drawn_number.number,board.n4 == drawn_number.number,board.n5 == drawn_number.number,board.g1 == drawn_number.number,board.g2 == drawn_number.number,board.g3 == drawn_number.number,board.g4 == drawn_number.number,board.g5 == drawn_number.number,board.o1 == drawn_number.number,board.o2 == drawn_number.number,board.o3 == drawn_number.number,board.o4 == drawn_number.number,board.o5 == drawn_number.number) )).group_by(board.board_id).all()
    
    data = {}
    
    for r in res:
        data[ int(r[0]) ]= r[1]
    
    
    return resp(data)

    '''SELECT b.board_id, COUNT(*) FROM board AS b, drawn_number AS d WHERE b.game_id = d.game_id AND
b.b1 = d.number OR
b.b2 = d.number OR
b.b3 = d.number OR
b.b4 = d.number OR
b.b5 = d.number OR
b.i1 = d.number OR
b.i2 = d.number OR
b.i3 = d.number OR
b.i4 = d.number OR
b.i5 = d.number OR
b.n1 = d.number OR
b.n2 = d.number OR
b.n3 = d.number OR
b.n4 = d.number OR
b.n5 = d.number OR
b.g1 = d.number OR
b.g2 = d.number OR
b.g3 = d.number OR
b.g4 = d.number OR
b.g5 = d.number OR
b.o1 = d.number OR
b.o2 = d.number OR
b.o3 = d.number OR
b.o4 = d.number OR
b.o5 = d.number GROUP BY b.board_id'''



@app.errorhandler(404)
def page_not_found(e):
    return resp(None, 404)

if __name__ == '__main__':
    app.run(debug=True)

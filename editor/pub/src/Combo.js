function Combo(selection, name) {
    this.name = name || "";
    this.parent = null;
    this.timeUntilReady = 0;
    this.timeUntilReset = 2000;
    this.followUps = [];
    this.selection = selection;
    this.hitboxSelections = [];
}

Combo.prototype.serialize = function() {
    var serializedFollowUps = [];
    for (var key in this.followUps) {
        serializedFollowUps.push(this.followUps[key].serialize());
    }
    var serializedHitboxes = [];
    for (var key in this.hitboxSelections) {
        serializedFollowUps.push(this.hitboxSelections[key].serialize());
    }

    return {
        name: this.name,
        timeUntilRead: this.timeUntilRead,
        timeUntilReset: this.timeUntilReset,
        selection: this.selection.serialize(),
        followUps: serializedFollowUps,
        hitboxSelections: serializedHitboxes
    };
}

Combo.prototype.restore = function(serialized) {
    var restoredFollowUps = [];
    for (var key in serialized.followUps) {
        var followUp = new Combo(null);
        followUp.restore(serialized.followUps[key]);
        restoredFollowUps.push(followUp);
    }
    
    var restoredHitboxes = [];
    for (var key in serialized.hitboxSelections) {
        var hitbox = new Selection();
        hitbox.restore(serialized.hitboxSelections[key]);
        restoredHitboxes.push(hitbox);
    }
    
    var restoredSelection = new Selection();
    restoredSelection.restore(serialized.selection);

    this.name = serialized.name;
    this.timeUntilRead = serialized.timeUntilRead;
    this.timeUntilReset = serialized.timeUntilReset;
    this.selection = restoredSelection,
    this.followUps = restoredFollowUps;
    this.hitboxSelections = restoredHitboxes;
}

Combo.prototype.getIndexInParent = function() {
    if (!this.parent) {
        return -1;
    }
    
    for (var i=0; i < this.parent.followUps.length; ++i) {
        if (this.parent.followUps[i] == this) {
            return i;
        }
    }
    return -2;
}

Combo.prototype.addFollowUp = function(nextCombo) {
    this.followUps.push(nextCombo);
    nextCombo.parent = this;
}

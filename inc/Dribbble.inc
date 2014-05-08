<?php
/**
 *  @file 
 *  Contains Dribbble class, which allows for interaction with the
 *  Dribbble API.
 */

class Dribbble {

  /**
   *  Dribbble API version.
   *
   *  @var
   */
  protected static $apiVersion = 'beta';

  /**
   *  Dribbble class client version.
   *
   *  @var
   */
  protected static $clientVersion = '0.1';

  /**
   *  Dribbble API URL base.
   *
   *  @var
   */
  protected static $urlBase = 'http://api.dribbble.com/';

  /**
   *  Make API request using drupal_http_request().
   *
   *  @param $endpoint string
   *    API endpoint to call.
   *
   *  @param $params string
   *    API method parameters. Converted to GET query parameters.
   *
   *  @param $method string
   *    HTTP method to implement.
   *
   *  @return mixed
   *    If $response->code === 200, then JSON decoded object is
   *    returned. Else returns FALSE.
   */
  public static function call($endpoint = FALSE, $params = FALSE, $method = 'GET') {

    $data = '';

    if (gettype($params) === 'array' && !empty($params)) {

      foreach ($params as $k => $v) {
        $data .= $k . '=' . $v . '&';
      }
      $data = rtrim($data, '&');

    }

    $options = array(
      'method' => $method,
      'data' => $data
    );

    $url = self::$urlBase . $endpoint;

    $response = drupal_http_request($url, $options);

    // dsm($response); dsm(json_decode($response->data));

    switch ($response->code) {

      case '200' :
        watchdog('dribbble', 'Dribbble API %method request to /%endpoint completed successfully.', array('%endpoint' => $endpoint, '%method' => $method), WATCHDOG_NOTICE);
        return json_decode($response->data);
        break;

      default :
        watchdog('dribbble', 'Dribbble API %method request to /%endpoint failed. Request returned code %code.', array('%endpoint' => $endpoint, '%method' => $method, '%code' => $response->code), WATCHDOG_ERROR);
        return FALSE;
        break;

    }

  }

  /**
   *  GET /shots/:id
   *
   *  Request a specific shot.
   *
   *  @param $id string
   *    ID of the shot to request.
   */
  public static function getShot($id = FALSE) {

    if (!$id) {
      return;
    }

    return self::call('shots/' . $id);

  }

  /**
   *  GET /shots/:id/rebounds
   *
   *  Request the rebounds of a specific shot.
   *
   *  @param $id string
   *    ID of the shot to request rebounds for.
   */
  public static function getShotRebounds($id = FALSE) {

    if (!$id) {
      return;
    }

    return self::call('shots/' . $id . '/rebounds');

  }

  /**
   *  GET /shots/:list
   *
   *  Request a list of recent shots.
   *
   *  @param $list string
   *    Name of the list to request. Can be debuts, everyone, or popular.
   *
   *  @param $params array
   *    API parameters to submit with this request. Supports [page], [per_page].
   */
  public static function getShotList($list = 'debuts', $params = array()) {

    return self::call('shots/' . $list, $params);

  }

  /**
   *  GET /players/:id/shots
   *
   *  Request a specific player's recent shots.
   *
   *  @param $id string
   *    Username of the player to request shots from.
   *
   *  @param $params array
   *    API parameters to submit with this request. Supports [page], [per_page].
   */
  public static function getPlayerShots($id = FALSE, $params = array()) {

    return self::call('players/' . $id . '/shots', $params);

  }

  /**
   *  GET /players/:id/shots/following
   *
   *  Request recent shots from those a specific player is following.
   *
   *  @param $id string
   *    Username of the player to request following shots from.
   *
   *  @param $params array
   *    API parameters to submit with this request. Supports [page], [per_page].
   */
  public static function getPlayerShotsFollowing($id = FALSE, $params = array()) {

    if (!$id) {
      return;
    }

    return self::call('players/' . $id . '/shots/following', $params);

  }

  /**
   *  GET /players/:id/shots/likes
   *
   *  Request shots a specific player has recently liked.
   *
   *  @param $id string
   *    Username of the player to request liked shots from.
   *
   *  @param $params array
   *    API parameters to submit with this request. Supports [page], [per_page].
   */
  public static function getPlayerShotsLikes($id = FALSE, $params = array()) {

    if (!$id) {
      return;
    }

    return self::call('players/' . $id . '/shots/likes', $params);

  }

  /**
   *  GET /players/:id
   *
   *  Request the profile of a specific player.
   *
   *  @param $id string
   *    Username of the player to request profile info from.
   */
  public static function getPlayer($id = FALSE) {

    if (!$id) {
      return;
    }

    return self::call('players/' . $id);

  }

  /**
   *  GET /players/:id/followers
   *
   *  Request the profiles of a specific player's followers.
   *
   *  @param $id string
   *    Username of the player to request follower profiles from.   
   */
  public static function getPlayerFollowers($id = FALSE) {

    if (!$id) {
      return;
    }

    return self::call('players/' . $id . '/followers');

  }

  /**
   *  GET /players/:id/following
   *
   *  Request the profiles of those a specific player is following.
   *
   *  @param $id string
   *    Username of the player to request following profiles from.      
   */
  public static function getPlayerFollowing($id = FALSE) {

    if (!$id) {
      return;
    }

    return self::call('players/' . $id . '/following');

  }

  /**
   *  GET /players/:id/draftees
   *
   *  Request the profiles of those a specific player has drafted.
   *
   *  @param $id string
   *    Username of the player to request draftee profiles from.      
   */
  public static function getPlayerDraftees($id = FALSE) {

    if (!$id) {
      return;
    }

    return self::call('players/' . $id . '/draftees');

  }

}